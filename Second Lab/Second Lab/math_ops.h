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
