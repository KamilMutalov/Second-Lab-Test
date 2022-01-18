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
