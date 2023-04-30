#include "s21_decimal.h"

int s21_is_less(s21_decimal num1, s21_decimal num2) {
  int result = -1;
  char d_flag = 'l';
  int num1_sign = get_sign(num1);
  int num2_sign = get_sign(num2);

  if (num1_sign == 0 && num2_sign == 0)
    result = dec_comparison(num1, num2, d_flag);
  else if (num1_sign == 1 && num2_sign == 1)
    result = dec_comparison(num1, num2, d_flag);
  else if (num1_sign == 1 && num2_sign == 0)
    result = 1;
  else if (num1_sign == 0 && num2_sign == 1)
    result = 0;
  return result;
}

int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2) {
  return (s21_is_less(num1, num2) || s21_is_equal(num1, num2));
}

int s21_is_greater(s21_decimal num1, s21_decimal num2) {
  int result = -1;
  char d_flag = 'g';
  int num1_sign = get_sign(num1);
  int num2_sign = get_sign(num2);

  if (num1_sign == 0 && num2_sign == 0)
    result = dec_comparison(num1, num2, d_flag);
  else if (num1_sign == 1 && num2_sign == 1)
    result = dec_comparison(num1, num2, d_flag);
  else if (num1_sign == 1 && num2_sign == 0)
    result = 0;
  else if (num1_sign == 0 && num2_sign == 1)
    result = 1;
  return result;
}

int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2) {
  return (s21_is_greater(num1, num2) || s21_is_equal(num1, num2));
}

int s21_is_equal(s21_decimal num1, s21_decimal num2) {
  int result = -1;
  char d_flag = 'e';
  int num1_sign = get_sign(num1);
  int num2_sign = get_sign(num2);

  if (num1_sign == 0 && num2_sign == 0)
    result = dec_comparison(num1, num2, d_flag);
  else if (num1_sign == 1 && num2_sign == 1)
    result = dec_comparison(num1, num2, d_flag);
  else if (num1_sign == 1 && num2_sign == 0)
    result = 0;
  else if (num1_sign == 0 && num2_sign == 1)
    result = 0;
  return result;
}

int s21_is_not_equal(s21_decimal num1, s21_decimal num2) {
  return !s21_is_equal(num1, num2);
}

int dec_comparison(s21_decimal num1, s21_decimal num2, char d_flag) {
  int result = -1;
  int inverted = 0;
  int match = 0;

  scale_equalize(&num1, &num2);
  if (get_sign(num1) == 1) {
    invert_bit(&(num1.bits[3]), 31);
    invert_bit(&(num2.bits[3]), 31);
    inverted = 1;
  }
  for (int i = 3; i > -1; i--) {
    if (num1.bits[i] != num2.bits[i]) {
      if (num1.bits[i] > num2.bits[i] && d_flag == 'g') {
        result = 1;
        break;
      } else if (num1.bits[i] < num2.bits[i] && d_flag == 'l') {
        result = 1;
        break;
      } else {
        result = 0;
        break;
      }
    } else
      match++;
  }
  if (match == 4 && d_flag == 'e') result = 1;
  if (is_zero(num1) == 1 && is_zero(num2) == 1) {
    if (d_flag == 'e') result = 1;
    if (d_flag == 'g' || d_flag == 'l') result = 0;
    if (d_flag == 'e' && (get_bit(num1, 127) == 1 || get_bit(num2, 127) == 1))
      result = 1;
  }
  if (inverted == 1 && d_flag != 'e') invert_bit((unsigned int*)&result, 0);
  return result;
}