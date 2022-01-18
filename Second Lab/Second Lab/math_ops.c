#include "math_ops.h"

uint1024_t add_op(const uint1024_t first, const uint1024_t second)
{
	uint64_t tmp_summ[32] = { 0 };
	int max_count_digits = max(first.count_digits, second.count_digits);

	for (int i = 0; i < max_count_digits; ++i)
	{
		tmp_summ[i] += (uint64_t)first.coeffs[i] + (uint64_t)second.coeffs[i];
		if (i == 31)
		{
			if (tmp_summ[i] / BASE_OF_U1024)
			{
				overflow_error();
			}
			return from_array_uint64_t(&tmp_summ);
		}

		tmp_summ[i + 1] = tmp_summ[i] / BASE_OF_U1024;
		tmp_summ[i] %= BASE_OF_U1024;
	}
	return from_array_uint64_t(&tmp_summ);
}

uint1024_t subtr_op(const uint1024_t first, const uint1024_t second)
{
	uint1024_t maximum, minimum;
	if (is_first_max(first, second))
	{
		maximum = first;
		minimum = second;
	}
	else
	{
		maximum = second;
		minimum = first;
	}
	uint64_t tmp_subtr[32] = { 0 };

	for (int i = 0; i < maximum.count_digits; ++i)
	{
		tmp_subtr[i] += BASE_OF_U1024 + maximum.coeffs[i] - minimum.coeffs[i];
		if (tmp_subtr[i] >= BASE_OF_U1024)
		{
			tmp_subtr[i] -= BASE_OF_U1024;
		}
		else
		{
			tmp_subtr[i + 1] = -1;
		}
	}
	return from_array_uint64_t(tmp_subtr);
}

uint1024_t mult_op(const uint1024_t first, const uint1024_t second)
{
	uint1024_t maximum, minimum;
	if (is_first_max(first, second))
	{
		maximum = first;
		minimum = second;
	}
	else
	{
		maximum = second;
		minimum = first;
	}

	if (maximum.count_digits + minimum.count_digits > U32_IN_U1024)
	{
		overflow_error();
	}

	uint1024_t multiply[U32_IN_U1024] = { from_uint32_t(0) };

	for (int i = 0; i < minimum.count_digits; ++i)
	{
		uint64_t tmp_mult[U32_IN_U1024] = { 0 };

		for (int j = 0; j < maximum.count_digits; ++j)
		{
			tmp_mult[j] += (uint64_t)maximum.coeffs[j] * (uint64_t)minimum.coeffs[i];
			tmp_mult[j + 1] = tmp_mult[j] >> 32;
			tmp_mult[j] %= BASE_OF_U1024;
		}
		multiply[i] = from_array_uint64_t(tmp_mult);
	}
	uint1024_t base_in_big_num = from_uint32_t(UINT_MAX);
	base_in_big_num = add_op(base_in_big_num, from_uint32_t(1));

	uint1024_t result = from_uint32_t(0);
	for (int i = 0; i < minimum.count_digits; ++i)
	{
		result = add_op(result, left_shift_op(multiply[i], i));
	}

	result.count_digits = get_amount_digits(result);
	return result;
}

uint1024_t pow_op(const uint1024_t big_num, const int grade)
{
	if (!grade)
	{
		return from_uint32_t(1);
	}

	uint1024_t result = big_num;
	if (grade == 1)
	{
		return result;
	}

	for (int i = 1; i < grade; ++i)
	{
		result = mult_op(result, big_num);
	}
	result.count_digits = get_amount_digits(result);
	return result;
}

int is_first_max(const uint1024_t first, const uint1024_t second)
{
	if (first.count_digits != second.count_digits)
	{
		return first.count_digits > second.count_digits;
	}
	for (int i = first.count_digits - 1; i > -1; --i)
	{
		if (first.coeffs[i] != second.coeffs[i])
		{
			return first.coeffs[i] > second.coeffs[i];
		}
	}
	return 1;
}

uint1024_t left_shift_op(const uint1024_t big_num, const int shift_times)
{
	if (big_num.count_digits + shift_times > U32_IN_U1024)
	{
		overflow_error();
	}
	uint1024_t shifted_num = from_uint32_t(0);

	for (int i = 0; i < big_num.count_digits; ++i)
	{
		shifted_num.coeffs[i + shift_times] = big_num.coeffs[i];
	}

	shifted_num.count_digits = get_amount_digits(shifted_num);
	return shifted_num;
}

uint32_t hex_to_int(const char* hex)
{
	const int HEX_BASE = 16;
	const int NUMBER_A_IN_HEX = 10;

	uint32_t result = 0;
	int position_hex_digit = strlen(hex) - 1;
	int decimal_digit;

	while (*hex)
	{
		if (*hex >= '0' && *hex <= '9')
		{
			decimal_digit = *hex - '0';
		}
		else if (*hex >= 'A' && *hex <= 'F')
		{
			decimal_digit = *hex - 'A' + NUMBER_A_IN_HEX;
		}
		else if ((*hex >= 'a' && *hex <= 'f'))
		{
			decimal_digit = *hex - 'a' + NUMBER_A_IN_HEX;
		}
		else
		{
			invalid_number_error();
		}

		result += decimal_digit * pow(HEX_BASE, position_hex_digit);
		--position_hex_digit;
		++hex;
	}

	return result;
}
