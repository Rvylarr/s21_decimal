#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exit_code = 0;
  int sign1 = get_bit(value_1, 127), sign2 = get_bit(value_2, 127);
  int scale1 = get_pow(value_1), scale2 = get_pow(value_2);
  if (scale1 != scale2) {
    scale_equalize(&value_1, &value_2);
    scale1 = get_pow(value_1);
  }
  set_bit(&value_1, 127, 0);
  set_bit(&value_2, 127, 0);
  while (s21_is_less(value_1, value_2) == 1) {
    mul_by_ten(&value_1);
    scale1++;
  }
  if (is_zero(value_2) == 1)
    exit_code = 3;
  else if ((sign1 == 1 && sign2 == 1) || (sign1 == 0 && sign2 == 0)) {
    exit_code = s21_division(value_1, value_2, result);
    abs_dec(*result);
    result->bits[3] = scale1;
  } else if ((sign1 == 1 && sign2 == 0) || (sign1 == 0 && sign2 == 1)) {
    set_bit(result, 127, 1);
    exit_code = s21_division(value_1, value_2, result);
    result->bits[3] = scale1;
    set_bit(result, 127, 1);
  }
  if (exit_code != 0) {
    for (int j = 3; j > -1; j--) result->bits[j] = 0;
  }
  return exit_code;
}

int s21_division(s21_decimal value_1, s21_decimal divisor,
                 s21_decimal *result) {
  s21_decimal dividend = {0};  // делимое
  s21_decimal difference = {0};  // вычитаемое для поиска остатка
  s21_decimal dec_max = {{4294967295, 4294967295, 4294967295, 0}};
  int result_sign = get_bit(*result, 127);
  int exit_code = 0;
  int i = 95;

  while (get_bit(*result, 95) != 1) {
    dividend.bits[3] = divisor.bits[3];
    left(result);
    set_bit(&dividend, 0, get_bit(value_1, i));
    if (s21_is_greater_or_equal(dividend, divisor) == 1) {
      s21_sub(dividend, divisor, &difference);
      dividend = difference;
      set_bit(result, 0, 1);
    }
    left(&dividend);
    i--;
    if (s21_is_equal(dividend, difference) == 1 &&
        s21_is_not_equal(dividend, *result) == 1 && i < 0)
      break;
  }
  set_bit(result, 127, result_sign);
  if ((result->bits[0] == dec_max.bits[0] &&
       result->bits[1] == dec_max.bits[1] &&
       result->bits[2] == dec_max.bits[2]) &&
      is_zero(dividend) != 0)
    exit_code = result_sign == 0 ? 1 : 2;
  return exit_code;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  memset(result, 0, sizeof(s21_decimal));
  int res = 0, sign1 = get_bit(value_1, 127), sign2 = get_bit(value_2, 127);
  int scale1 = get_pow(value_1), scale2 = get_pow(value_2);
  if (scale1 + scale2 > 28) res = 2;
  for (int i = 0; i <= first_bit(value_1); i++) {
    if (get_bit(value_1, i) == 1) {
      bit_addition(value_2, *result, result);
    }
    if (first_bit(value_2) != 95) {
      left(&value_2);
    } else {
      if (sign1 != sign2) {
        res = 2;
      } else {
        res = 1;
      }
      break;
    }
  }
  set_pow(*result, result, scale1 + scale2);
  if (sign1 != sign2) set_bit(result, 127, 1);
  return res;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  memset(result, 0, sizeof(s21_decimal));
  int res = 0, sign1 = get_bit(value_1, 127), sign2 = get_bit(value_2, 127);
  int scale1 = get_pow(value_1), scale2 = get_pow(value_2);
  if (scale1 != scale2) {
    scale_equalize(&value_1, &value_2);
    scale1 = get_pow(value_1);
  }
  if (sign1 != sign2) {
    set_bit(&value_2, 127, sign1);
    res = s21_add(value_1, value_2, result);
  } else {
    if (s21_is_greater_or_equal(abs_dec(value_1), abs_dec(value_2))) {
      bit_substraction(value_1, value_2, result);
      set_bit(result, 127, sign1);
    } else {
      bit_substraction(value_2, value_1, result);
      set_bit(result, 127, sign2 == 0 ? 1 : 0);
    }
  }
  set_pow(*result, result, scale1);
  return res;
}

void bit_substraction(s21_decimal value1, s21_decimal value2,
                      s21_decimal *res) {
  int bit1, bit2, tmp = 0, sub;
  for (int i = 0; i < 96; i++) {
    bit1 = get_bit(value1, i);
    bit2 = get_bit(value2, i);
    sub = bit1 - bit2;
    switch (sub) {
      case (-1): {
        set_bit(res, i, 1);
        tmp = 1;
        break;
      }
      case (0): {
        set_bit(res, i, 0);
        break;
      }
      case (1): {
        set_bit(res, i, 1);
        break;
      }
    }
    if (tmp == 1) {
      for (int j = i; j < 96; j++) {
        if (get_bit(value1, j) == 1) {
          set_bit(&value1, j, 0);
          break;
        } else {
          set_bit(&value1, j, 1);
        }
      }
      tmp = 0;
    }
  }
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  memset(result, 0, sizeof(s21_decimal));
  int res = 0, sign1 = get_bit(value_1, 127), sign2 = get_bit(value_2, 127);
  int scale1 = get_pow(value_1), scale2 = get_pow(value_2);
  int frt1 = first_bit(value_1), frt2 = first_bit(value_2);
  if (scale1 != scale2) {
    scale_equalize(&value_1, &value_2);
  }
  if (sign1 == sign2) {
    bit_addition(value_1, value_2, result);
    set_bit(result, 127, sign1);
    int frtres = first_bit(*result);
    if (frt1 > frtres || frt2 > frtres ||
        (sign1 == 0 && frt1 == 95 && frt2 == 95)) {
      if (sign1) {
        memset(result, 0, sizeof(s21_decimal));
        res = 2;
      } else {
        memset(result, 0, sizeof(s21_decimal));
        res = 1;
      }
    }
    set_pow(*result, result, get_pow(value_1));
  } else {
    if (sign1 == 1) {
      set_bit(&value_1, 127, 0);
      s21_sub(
          value_2, value_1,
          result);
    } else {
      set_bit(&value_2, 127, 0);
      s21_sub(value_1, value_2, result);
    }
  }
  return res;
}

void scale_equalize(s21_decimal *value1, s21_decimal *value2) {
  s21_decimal *min = NULL, *max = NULL;
  int flag = 0;
  int scale1 = get_pow(*value1), scale2 = get_pow(*value2);
  if (scale1 > scale2) {
    min = value2;
    max = value1;
  } else {
    SWAP(scale1, scale2, int);
    min = value1;
    max = value2;
  }
  for (int i = scale1 - scale2; (i > 0 && flag == 0); i--) {
    flag = scale_increase(min);
  }
  scale1 = get_pow(*value1);
  scale2 = get_pow(*value2);
  while (scale1 != scale2) {
    scale_decrease(max);
    scale2++;
  }
}

int scale_increase(s21_decimal *value) {
  int res = 0;
  int scale = get_pow(*value);
  if (first_bit(*value) < 93 && scale < 28) {
    s21_decimal tmp8 = {0}, tmp2 = {0};
    dec_copy(*value, &tmp2);
    dec_copy(*value, &tmp8);
    for (int i = 0; i < 3; i++) left(&tmp8);
    left(&tmp2);
    bit_addition(tmp8, tmp2, value);
    set_pow(*value, value, scale + 1);
  } else {
    res = 1;
  }
  return res;
}

void scale_decrease(s21_decimal *value) {
  int scale = get_pow(*value);
  div_by_ten(value);
  set_pow(*value, value, scale - 1);
}

void left(s21_decimal *value) {
  int bit31 = get_bit(*value, 31);
  int bit63 = get_bit(*value, 63);
  value->bits[0] <<= 1;
  value->bits[1] <<= 1;
  value->bits[2] <<= 1;
  if (bit31) set_bit(value, 32, 1);
  if (bit63) set_bit(value, 64, 1);
}

void dec_copy(s21_decimal og, s21_decimal *res) {
  for (int i = 0; i < 128; i++) {
    set_bit(res, i, get_bit(og, i));
  }
}

void bit_addition(s21_decimal value1, s21_decimal value2, s21_decimal *res) {
  int tmp = 0, sum = 0;
  for (int i = 0; i < 96; i++) {
    sum = get_bit(value1, i) + get_bit(value2, i);
    if (sum == 2) {
      if (tmp == 1) {
        set_bit(res, i, 1);
      } else {
        set_bit(res, i, 0);
        tmp = 1;
      }
    } else if (sum == 1) {
      if (tmp == 1) {
        set_bit(res, i, 0);
      } else {
        set_bit(res, i, 1);
      }
    } else if (sum == 0) {
      if (tmp == 1) {
        set_bit(res, i, 1);
        tmp = 0;
      } else {
        set_bit(res, i, 0);
      }
    }
  }
}

int first_bit(s21_decimal value) {
  int bit = 95;
  for (; bit >= 0 && get_bit(value, bit) == 0; bit--) {
  }
  return bit;
}

s21_decimal abs_dec(s21_decimal value) {
  if (get_bit(value, 127) != 0) set_bit(&value, 127, 0);
  return value;
}