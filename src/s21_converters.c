#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int result = 0;
  if (src > INT_MAX || src < INT_MIN) result = 1;
  if (dst && !result) {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    if (src < 0) {
      s21_negate(*dst, dst);
      src = -src;
    }
    dst->bits[0] = src;
  } else {
    result = 1;
  }
  return result;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int result = 0;
  if (src.bits[1] || src.bits[2]) {
    result = 1;
  }
  if (dst && !result) {
    // memset(dst, 0, sizeof(int) * 4);
    *dst = src.bits[0];
    if (get_bit(src, 127)) {
      *dst *= -1;
    }
  } else {
    result = 1;
  }
  return result;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int result = 0, i = 0;
  double qwe = 0;
  if (dst != NULL) {
    for (; i < 96; i++) {
      if (get_bit(src, i)) {
        qwe += pow(2, i);
      }
    }
    int scale = get_pow(src);
    while (scale) {
      qwe /= 10;
      scale--;
    }
    if (get_bit(src, 127)) {
      qwe *= -1;
    }
    *dst = (float)qwe;
  } else {
    result = 1;
  }
  return result;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int result = 0;
  if (isnan(src) || isinf(src)) {
    result = 1;
  }
  if (dst && !result) {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    int sign = 0;
    if (src < 0) {
      sign = 1;
      src = -(src);
    }
    int new = (int)src;
    int exp = 0;
    while (src - ((float)new / (int)(pow(10, exp))) != 0) {
      exp++;
      new = src *(int)(pow(10, exp));
    }
    s21_from_int_to_decimal(new, dst);

    if (sign) {
      s21_negate(*dst, dst);
    }
    dst->bits[3] += exp << 16;
  } else {
    result = 1;
  }
  return result;
}