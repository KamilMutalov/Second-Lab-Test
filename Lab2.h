#pragma once
#ifndef __LAB2__
#define __LAB2__

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>

#define U32_IN_U1024 32
#define HEXED_MAX_LENGTH 256
#define max(a, b) (((a) > (b)) ? (a) : (b))

extern const uint64_t BASE_OF_U1024;
extern const int GRADES_OF_HEX_IN_U1024;

typedef struct uint1024
{
	uint32_t coeffs[U32_IN_U1024];
	int count_digits;
} uint1024_t;

void overflow_error();
void invalid_number_error();
uint1024_t from_uint32_t(const uint32_t number);
uint1024_t from_array_uint64_t(const uint64_t* const array_uint64_t);
int get_amount_digits(const uint1024_t big_num);
int get_amount_digits_uint64_t(const uint64_t* const array_uint64_t);
char* printf_value(const uint1024_t big_num);
void scanf_value(uint1024_t* big_num, char* str);
uint1024_t add_op(const uint1024_t first, const uint1024_t second);
uint1024_t subtr_op(const uint1024_t first, const uint1024_t second);
uint1024_t mult_op(const uint1024_t first, const uint1024_t second);
uint1024_t pow_op(const uint1024_t big_num, const int grade);
int is_first_max(const uint1024_t first, const uint1024_t second);
uint1024_t left_shift_op(const uint1024_t big_num, const int shift_times);
uint32_t hex_to_int(const char* hex);

#endif // !__LAB2__

