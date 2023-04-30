#ifndef _S21_DECIMAL_H
#define _S21_DECIMAL_H

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINUS_SIGN 2147483648
enum state { FALSE, TRUE };
#define START_INFO 96
#define SWAP(x, y, T) \
  do {                \
    T SWAP = x;       \
    x = y;            \
    y = SWAP;         \
  } while (0)

typedef struct {
  unsigned int bits[4];
} s21_decimal;

// ================= base functions =================
void dec_output(s21_decimal num);
void numbered_dec_output(s21_decimal num);
void set_bit(s21_decimal *decl, int index, int bit);
int get_bit(s21_decimal decl, int index);

// ================= initialization functions =================
void init_decimal(s21_decimal *decimal);
void set_sign(s21_decimal *decl, int sign);
int set_pow(s21_decimal value, s21_decimal *result, int pow);

// ================= check functions =================
int get_sign(s21_decimal decl);
int get_pow(s21_decimal value);

// ================= converter functions =================
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);

// ================= arithmetic functions =================
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

s21_decimal abs_dec(s21_decimal value);
void scale_equalize(s21_decimal *value1, s21_decimal *value2);
void left(s21_decimal *value);
int scale_increase(s21_decimal *value);
void scale_decrease(s21_decimal *value);
void dec_copy(s21_decimal og, s21_decimal *res);
void bit_substraction(s21_decimal value1, s21_decimal value2, s21_decimal *res);
void bit_addition(s21_decimal value1, s21_decimal value2, s21_decimal *res);
int first_bit(s21_decimal value);

// ================= comparison functions =================
int s21_is_less(s21_decimal num1, s21_decimal num2);
int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2);
int s21_is_greater(s21_decimal num1, s21_decimal num2);
int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2);
int s21_is_equal(s21_decimal num1, s21_decimal num2);
int s21_is_not_equal(s21_decimal num1, s21_decimal num2);

void invert_bit(unsigned int *value, int BitNumber);
int dec_comparison(s21_decimal num1, s21_decimal num2, char d_flag);

// ================= other functions =================
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

void div_by_ten(s21_decimal *value);
void mul_by_ten(s21_decimal *value);
int is_zero(s21_decimal value);
int s21_division(s21_decimal value_1, s21_decimal divisor, s21_decimal *result);

#endif  // _S21_DECIMAL_H