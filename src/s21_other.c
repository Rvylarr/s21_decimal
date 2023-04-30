#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  int int_pow = 0;
  *result = value;

  if (result == NULL)
    error = 1;
  for (int i = 126; i >= 96 && !error; i--) {
    if ((i > 119 || i < 112) && get_bit(value, i))
      error = 1;
    else if ((i < 120 && i > 111)) {
      int_pow += get_bit(value, i) * pow(2, i - 112);
      if (int_pow > 28)
        error = 1;
    }
  }
  if (!error && int_pow) {
    for (int i = 119; i > 111; i--)
      set_bit(result, i, 0);
    for (int i = 0; i < int_pow; i++)
      div_by_ten(result);
  }
  return error;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
    int error = 0;
  *result = value;

  if (result == NULL)
    error = 1;
  for (int i = 126; i > 95 && !error; i--) {
    if ((i > 119 || (i < 112 && i > 95)) && get_bit(value, i))
      error = 1;
  }
  if (!error)
    set_bit(result, 127, !get_bit(value, 127));
  return error;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 0;
  int zero_value = 1;

  for (int i = 95; i >= 0 && zero_value; i--)
    if (get_bit(value, i)) zero_value = 0;
  error = s21_truncate(value, result);
  if (!error && !zero_value && get_bit(*result, 127) &&
      get_pow(value)) {
    int i = 0;
    while (get_bit(*result, i)) {
      set_bit(result, i, 0);
      i++;
    }
    set_bit(result, i, 1);
  }
  return error;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0;
  int zero_value = 1;

  for (int i = 95; i >= 0 && zero_value; i--)
    if (get_bit(value, i)) zero_value = 0;
  error = s21_truncate(value, result);
  if (!error && !zero_value && get_pow(value)) {
    s21_decimal diff = {0};
    s21_sub(value, *result, &diff);
    s21_decimal zerohalf = {0};
    s21_from_int_to_decimal(5, &zerohalf);
    set_pow(zerohalf, &zerohalf, 1);
    if (s21_is_greater_or_equal(abs_dec(diff),
                                zerohalf)) {
      int i = 0;
      while (get_bit(*result, i)) {
        set_bit(result, i, 0);
        i++;
      }
      set_bit(result, i, 1);
    }
  }
  return error;
}