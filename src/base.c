#include "s21_decimal.h"

// ================= base functions =================
void dec_output(s21_decimal num) {
  int size = sizeof(num.bits[0]) * 8 - 1;
  for (int j = 3; j >= 0; j--) {
    for (int i = size; i >= 0; i--) {
      printf("%d", num.bits[j] & (1 << i) ? 1 : 0);
    }
    if (j != 0) printf("\n");
  }
  printf("\n");
}

void numbered_dec_output(s21_decimal num) {
  int size = sizeof(num.bits[0]) * 8 - 1;
  int ii = 127;
  for (int j = 3; j >= 0; j--) {
    printf("| %3d |", ii);
    for (int i = size; i >= 0; i--) {
      printf("%3d_", ii);
      ii--;
    }
    printf("| %3d |\n", ii + 1);
    ii += size + 1;
    printf("|bit %d|", j);
    for (int i = size; i >= 0; i--) {
      if ((ii < 127 && ii > 119) || (ii < 112 && ii > 95)) {
        printf(" NU ");
      } else {
        printf("% 3d ", num.bits[j] & (1 << i) ? 1 : 0);
      }
      ii--;
    }
    printf("|     | \n");
  }
}

void set_bit(s21_decimal *decl, int index, int bit) {
  int ind32 = index / 32, num32 = index % 32;
  if (bit == 1) {
    decl->bits[ind32] |= (1u << num32);
  } else {
    decl->bits[ind32] &= (~((1u) << num32));
  }
}

int get_bit(s21_decimal decl, int index) {
  int ind32 = index / 32, num32 = index % 32;
  return (decl.bits[ind32] & (1u << num32)) >> num32;
}

int set_pow(s21_decimal value, s21_decimal *result, int int_pow) {
  int error = 0;
  *result = value;
  if (result == NULL) {
    error = 1;
  }
  if (int_pow <= 28) {
    for (int i = 112; i < 120; i++) {
      if (fmod(int_pow, 2))
        set_bit(result, i, 1);
      else
        set_bit(result, i, 0);
      int_pow = int_pow / 2;
    }
  } else {
    error = 1;
  }
  return error;
}

int get_pow(s21_decimal value) {
  int power = 0;
  int counter = 0;
  int length = 16;
  int bit = 0;
  while (length <= 23) {
    bit = ((value.bits[3] & (1 << length)) != 0);
    power += bit * pow(2, counter);
    length++;
    counter++;
  }
  return power;
}

void init_decimal(s21_decimal *decimal) {
  for (int i = 0; i < 4; i++) {
    decimal->bits[i] = 0;
  }
}