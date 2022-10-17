#pragma once
#ifndef Constructors_h
#define Constructors_h
#include "defines.h"

uint1024_t from_uint32_t(const uint32_t number);
uint1024_t from_array_uint64_t(const uint64_t* const array_uint64_t);
int get_amount_digits(const uint1024_t big_num);
int get_amount_digits_uint64_t(const uint64_t* const array_uint64_t);

#endif

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

#pragma once
#ifndef Defines_h
#define Defines_h

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>

#define U32_IN_U1024 32

typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef char* string;
extern const uint64_t BASE_OF_U1024;
extern const int GRADES_OF_HEX_IN_U1024;

typedef struct uint1024
{
	uint32_t coeffs[U32_IN_U1024];
	int count_digits;
} uint1024_t;

#endif

#include "defines.h"

const uint64_t BASE_OF_U1024 = (uint64_t)UINT_MAX + 1;
const int GRADES_OF_HEX_IN_U1024 = 8;

#pragma once
#ifndef Math_ops_h
#define Math_ops_h
#include "defines.h"
#include "constructors.h"

uint1024_t add_op(const uint1024_t first, const uint1024_t second);
uint1024_t subtr_op(const uint1024_t first, const uint1024_t second);
uint1024_t mult_op(const uint1024_t first, const uint1024_t second);
uint1024_t pow_op(const uint1024_t big_num, const int grade);
int is_first_max(const uint1024_t first, const uint1024_t second);
uint1024_t left_shift_op(const uint1024_t big_num, const int shift_times);
uint32_t hex_to_int(const char* hex);

#endif // !Math_ops_h

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

#include "defines.h"
#include "constructors.h"
#include "math_ops.h"

void overflow_error()
{
	printf("---------------------\n");
	printf("Error: overflow error\a\n");
	printf("---------------------\n");
	exit(-1);
}

void invalid_number_error()
{
	printf("---------------------\n");
	printf("Error: invalid number\a\n");
	printf("---------------------\n");
	exit(-1);
}

void printf_value(const uint1024_t big_num)
{
	int count_zeros_prev = 0;
	int count_zeros_curr;
	int delta_curr_prev;
	
	for (int i = big_num.count_digits - 1; i >= 0; --i)
	{
		count_zeros_curr = GRADES_OF_HEX_IN_U1024 * i;

		delta_curr_prev = count_zeros_prev - count_zeros_curr - snprintf(NULL, 0, "%X", big_num.coeffs[i]);

		for (int j = 0; j < delta_curr_prev; ++j)
		{
			printf("%X", 0);
		}
		printf("%X", big_num.coeffs[i]);
		count_zeros_prev = count_zeros_curr;
	}
	
}

void scanf_value(uint1024_t* big_num)
{
	*big_num = from_uint32_t(0);
	char buffer[257];
	if (!scanf("%s", buffer))
	{
		invalid_number_error();
	}

	int buff_length = strlen(buffer);
	big_num->count_digits = buff_length / GRADES_OF_HEX_IN_U1024;

	if (strlen(buffer) % GRADES_OF_HEX_IN_U1024)
	{
		big_num->count_digits += 1;
	}

	for (int i = 0; i < big_num->count_digits; ++i)
	{
		buff_length = strlen(buffer);
		if (buff_length <= GRADES_OF_HEX_IN_U1024)
		{
			big_num->coeffs[i] = hex_to_int(buffer);
			return;
		}

		char hex_digit[9];
		int position_digit = buff_length - GRADES_OF_HEX_IN_U1024;
		sprintf(hex_digit, "%s", buffer + position_digit);
		buffer[position_digit] = '\0';
		
		big_num->coeffs[i] = hex_to_int(hex_digit);
	}
	

}

int main(int argc, char** argv)
{
	
	uint1024_t x;
	uint1024_t y;
	printf("Set first number\n");
	scanf_value(&x);
	
	printf_value(pow_op(x, 5));
	return 0;
}

