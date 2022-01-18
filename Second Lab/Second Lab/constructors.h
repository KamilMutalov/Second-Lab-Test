#pragma once
#ifndef Constructors_h
#define Constructors_h
#include "defines.h"

uint1024_t from_uint32_t(const uint32_t number);
uint1024_t from_array_uint64_t(const uint64_t* const array_uint64_t);
int get_amount_digits(const uint1024_t big_num);
int get_amount_digits_uint64_t(const uint64_t* const array_uint64_t);

#endif
