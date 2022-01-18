#include "constructors.h"

uint1024_t from_uint32_t(const uint32_t number)
{
	uint1024_t new_num;
	for (int i = 1; i < U32_IN_U1024; ++i)
	{
		new_num.coeffs[i] = 0;
	}
	new_num.coeffs[0] = number;
	new_num.count_digits = 1;
	return new_num;
}

uint1024_t from_array_uint64_t(const uint64_t* const array_uint64_t)
{
	uint1024_t new_num;

	new_num.count_digits = get_amount_digits_uint64_t(array_uint64_t);
	for (int i = 0; i < U32_IN_U1024; ++i)
	{
		new_num.coeffs[i] = array_uint64_t[i];
	}

	return new_num;
}

int get_amount_digits(const uint1024_t big_num)
{
	int index_biggest_digit = 0;
	int amount_digits = 0;

	for (int i = U32_IN_U1024 - 1; i > -1; --i)
	{
		if (big_num.coeffs[i])
		{
			index_biggest_digit = i;
			break;
		}
	}

	for (int i = 0; i <= index_biggest_digit; ++i)
	{
		++amount_digits;
	}
	return amount_digits;
}

int get_amount_digits_uint64_t(const uint64_t* const array_uint64_t)
{
	int index_biggest_digit = 0;
	int amount_digits = 0;

	for (int i = U32_IN_U1024 - 1; i > -1; --i)
	{
		if (array_uint64_t[i])
		{
			index_biggest_digit = i;
			break;
		}
	}

	for (int i = 0; i <= index_biggest_digit; ++i)
	{
		++amount_digits;
	}
	return amount_digits;
}
