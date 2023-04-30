#include "s21_decimal.h"

int get_sign(s21_decimal decl) {
  int sign = get_bit(decl, 127);
  return sign;
}

void set_sign(s21_decimal *decl, int sign) { set_bit(decl, 127, sign); }

void invert_bit(unsigned int *value, int BitNumber) {
  *value ^= (1 << BitNumber);
}

void div_by_ten(s21_decimal *value) {
  long initial = 0;
  int rest = 0;
  for (int i = 2; i >= 0; i--) {
    initial = rest * 4294967296 + value->bits[i];
    value->bits[i] = initial / 10;
    rest = initial - value->bits[i] * 10;
  }
}

int is_zero(s21_decimal value) {
  int error = 0;
  s21_decimal zero_value = {{0, 0, 0, 0}};
  for (int i = 2; i > -1; i--) {
    if (value.bits[i] != zero_value.bits[i]) error++;
  }
  return error == 0 ? 1 : 0;
}

void mul_by_ten(s21_decimal *value) {
  s21_decimal ten = {0};
  s21_decimal result = {0};
  ten.bits[0] = 10;
  ten.bits[1] = 0;
  ten.bits[2] = 0;
  ten.bits[3] = 0;
  s21_mul(*value, ten, &result);
  for (int j = 2; j > -1; j--) value->bits[j] = result.bits[j];
}