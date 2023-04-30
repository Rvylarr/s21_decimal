#include <check.h>

#include "s21_decimal.h"

void run_test(Suite *thesuit) {
  SRunner *therunner = srunner_create(thesuit);
  srunner_set_fork_status(therunner, CK_NOFORK);
  srunner_run_all(therunner, CK_NORMAL);
  srunner_ntests_failed(therunner);
  srunner_free(therunner);
  printf("\n");
}

//================= arithmetic functions tests =================
// add
START_TEST(part1_add_normal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {{1535}};
  value_1.bits[0] = 150;
  value_2.bits[0] = 35;
  set_pow(value_2, &value_2, 1);
  int res = s21_add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_pow(result), 1);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(part1_add_both_neg) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {{1535}};
  value_1.bits[0] = 150;
  value_2.bits[0] = 35;
  set_sign(&value_2, 1);
  set_sign(&value_1, 1);
  set_pow(value_2, &value_2, 1);
  int res = s21_add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_pow(result), 1);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(part1_add_error) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 35;
  int res = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(res, 1);
  set_sign(&value_2, 1);
  set_sign(&value_1, 1);

  memset(&result, 0, sizeof(s21_decimal));
  res = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(part1_add_one_greater) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 540;
  value_2.bits[0] = 560;
  s21_decimal test = {{20}};
  set_sign(&value_2, 1);
  s21_add(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(part1_add_one_sign) {
  s21_decimal value_1 = {{150}};
  s21_decimal value_2 = {{50}};
  s21_decimal result = {0};
  s21_decimal test = {{100}};
  set_sign(&value_1, 1);
  s21_add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_pow(result), 0);
  ck_assert_int_eq(get_sign(result), 1);
  set_sign(&value_1, 0);
  set_sign(&value_2, 1);
  memset(&result, 0, sizeof(s21_decimal));
  int res = s21_add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_pow(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(res, 0);
}
END_TEST

// sub
START_TEST(part1_sub_normal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 155;
  value_2.bits[0] = 55;
  s21_sub(value_1, value_2, &result);
  s21_decimal test = {0};
  test.bits[0] = 100;
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  memset(&result, 0, sizeof(s21_decimal));
  value_1.bits[0] = (unsigned int)50;
  value_2.bits[0] = (unsigned int)150;
  s21_sub(value_1, value_2, &result);
  int sign = get_sign(result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(sign, 1);

  memset(&value_1, 0, sizeof(s21_decimal));
  memset(&value_2, 0, sizeof(s21_decimal));
  memset(&result, 0, sizeof(s21_decimal));
  value_1.bits[0] = (unsigned int)50;
  value_2.bits[0] = (unsigned int)15;
  memset(&result, 0, sizeof(s21_decimal));
  set_pow(value_2, &value_2, 1);
  s21_sub(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], 485);
  ck_assert_uint_eq(get_pow(result), 1);
  ck_assert_uint_eq(get_sign(result), 0);
}
END_TEST

START_TEST(part1_sub_inf) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 55;
  set_sign(&value_1, 1);
  int res = s21_sub(value_1, value_2, &result);
  ck_assert_uint_eq(res, 2);
}
END_TEST

START_TEST(part1_sub_one_sign) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 150;
  value_2.bits[0] = 50;
  set_sign(&value_1, 1);
  s21_sub(value_1, value_2, &result);
  s21_decimal test = {0};
  test.bits[0] = 200;
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  int sign = get_sign(result);
  ck_assert_int_eq(sign, 1);
  memset(&result, 0, sizeof(s21_decimal));
  set_sign(&value_1, 0);
  set_sign(&value_2, 1);
  s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  int sign1 = get_sign(result);
  ck_assert_int_eq(sign1, 0);
}
END_TEST

START_TEST(part1_sub_two_sign) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 150;
  value_2.bits[0] = 50;
  set_sign(&value_1, 1);
  set_sign(&value_2, 1);

  s21_sub(value_1, value_2, &result);
  s21_decimal test = {0};
  test.bits[0] = 100;
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  int sign = get_sign(result);
  ck_assert_int_eq(sign, 1);
  memset(&result, 0, sizeof(s21_decimal));
  s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  int sign1 = get_sign(result);
  ck_assert_int_eq(sign1, 1);
  value_1.bits[0] = 50;
  value_2.bits[0] = 150;
  memset(&result, 0, sizeof(s21_decimal));
  s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  sign1 = get_sign(result);
  ck_assert_int_eq(sign1, 0);
}
END_TEST

// mult
START_TEST(part1_mult_value_1_is_one) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 1;
  value_2.bits[0] = 10;
  test.bits[0] = 10;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  set_sign(&value_1, 1);
  memset(&result, 0, sizeof(s21_decimal));
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_sign(result), 1);
}
END_TEST

START_TEST(part1_mult_value_2_is_one) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 15;
  value_2.bits[0] = 1;
  test.bits[0] = 15;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
}
END_TEST

START_TEST(part1_mult_value_1_is_zero) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 0;
  value_2.bits[0] = 100;
  test.bits[0] = 0;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
}
END_TEST

START_TEST(part1_mult_value_2_is_zero) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 7;
  value_2.bits[0] = 0;
  test.bits[0] = 0;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
}
END_TEST

START_TEST(part1_mult_max) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 5;
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(res, 1);

  set_sign(&value_2, 1);
  res = s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(res, 2);
}
END_TEST

START_TEST(part1_mult_big_power) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 2147483647;
  value_2.bits[0] = 255;
  test.bits[0] = 2147483393;
  test.bits[1] = 127;
  set_pow(value_2, &value_2, 10);
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
  ck_assert_uint_eq(get_pow(result), 10);
  ck_assert_uint_eq(get_sign(result), 0);
  ck_assert_uint_eq(res, 0);
}
END_TEST

START_TEST(part1_mult_big_negative_over) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 2147483647;
  value_1.bits[1] = 2147483647;
  value_1.bits[2] = 2147483647;
  value_2.bits[0] = 15;
  set_pow(value_2, &value_2, 1);
  set_sign(&value_2, 1);
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(res, 2);
}
END_TEST

START_TEST(part1_mult_big_over) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 2147483647;
  value_1.bits[1] = 2147483647;
  value_1.bits[2] = 2147483647;
  value_2.bits[0] = 15;
  set_pow(value_2, &value_2, 1);
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(res, 1);
}
END_TEST

START_TEST(part1_mult_value_1_is_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  set_sign(&value_1, 1);
  value_1.bits[0] = 15;
  value_2.bits[0] = 1;
  test.bits[0] = 15;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_sign(result), 1);
}
END_TEST

START_TEST(part1_mult_value_2_is_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 15;
  set_sign(&value_2, 1);
  value_2.bits[0] = 1;
  test.bits[0] = 15;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_sign(result), 1);
}
END_TEST

START_TEST(part1_mult_value_1_is_zero_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  set_sign(&value_1, 1);
  value_1.bits[0] = 0;
  value_2.bits[0] = 100;
  test.bits[0] = 0;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_sign(result), 1);
}
END_TEST

START_TEST(part1_mult_value_2_is_zero_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 7;
  set_sign(&value_2, 1);
  value_2.bits[0] = 0;
  test.bits[0] = 0;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_sign(result), 1);
}
END_TEST

START_TEST(part1_mult_value_1_2_is_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  set_sign(&value_1, 1);
  set_sign(&value_2, 1);
  value_1.bits[0] = 0;
  value_2.bits[0] = 100;
  test.bits[0] = 0;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_sign(result), 0);
  set_pow(value_1, &value_1, 5);
  set_pow(value_2, &value_2, 29);
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
}
END_TEST

// === division === //
START_TEST(div_0) {
  s21_decimal value_1 = {{20, 0, 0, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {0};
  test.bits[0] = 10;
  set_bit(&value_1, 127, 0);
  set_bit(&value_2, 127, 1);
  int res = s21_div(value_1, value_2, &result);
  // dec_output(result);
  // printf("RES: %d\n", res);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_bit(result, 127), 1);
  ck_assert_uint_eq(get_pow(result), 0);
  ck_assert_uint_eq(res, 0);
}
END_TEST

START_TEST(div_1) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{3, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_2) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  set_pow(val1, &val1, ~(UINT_MAX / 2));
  set_pow(val2, &val2, ~(UINT_MAX / 2));
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_3) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_4) {  // тут как по мне должно быть норм
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  set_bit(&val1, 127, 0);
  set_bit(&val2, 127, 0);
  set_pow(val1, &val1, 1);
  set_pow(val2, &val2, 3);
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_5) {
  s21_decimal value_1 = {{4, 0, 0, 0}};
  s21_decimal value_2 = {{4, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {0};
  set_pow(value_1, &value_1, 0);
  set_pow(value_2, &value_2, 3);
  test.bits[0] = 1000;
  int res = s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_bit(result, 127), 0);
  ck_assert_uint_eq(get_pow(result), 0);
  ck_assert_uint_eq(res, 0);
}
END_TEST

START_TEST(div_6) {  // делимое меньше нечётного делителя
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{2, 0, 0, 1}};
  set_pow(value_1, &value_1, 0);
  set_pow(value_2, &value_2, 0);
  int res = s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(s21_is_equal(result, test), 1);
  ck_assert_uint_eq(get_bit(result, 127), 0);
  ck_assert_uint_eq(res, 0);
}
END_TEST

START_TEST(div_7) {  // тест переполнения 1
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 1}};
  s21_decimal value_2 = {{1, 0, 0, 1}};
  s21_decimal result = {0};
  set_pow(value_1, &value_1, 0);
  set_pow(value_2, &value_2, 0);
  int res = s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(res, 1);
}
END_TEST

START_TEST(div_8) {  // тест переполнения 2
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 1}};
  s21_decimal value_2 = {{1, 0, 0, 1}};
  s21_decimal result = {0};
  set_bit(&value_1, 127, 1);
  set_pow(value_1, &value_1, 0);
  set_pow(value_2, &value_2, 0);
  int res = s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(res, 2);
}
// END_TEST
// END OF baggmela tests

//================= comparison functions tests =================
// === is_less === //
START_TEST(is_less_plus_both) {  // 1337 < 1338 == 1 yes
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1338, &num2);
  ck_assert_int_eq(1, s21_is_less(num1, num2));
}
END_TEST

START_TEST(is_less_min_num1) {  // -1337 < 1338 == 1 yes
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(-1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1338, &num2);
  ck_assert_int_eq(1, s21_is_less(num1, num2));
}
END_TEST

START_TEST(is_less_min_num2) {  // 1337 < -1338 == 0 no
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(-1338, &num2);
  ck_assert_int_eq(0, s21_is_less(num1, num2));
}
END_TEST

START_TEST(is_less_min_both) {  // -1337 < -1338 == 0 no
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(-1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(-1338, &num2);
  ck_assert_int_eq(0, s21_is_less(num1, num2));
}
END_TEST

// === is_greater === //
START_TEST(is_greater_plus_both) {  // 1337 > 1338 == 0 no
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1338, &num2);
  ck_assert_int_eq(0, s21_is_greater(num1, num2));
}
END_TEST

START_TEST(is_greater_min_num1) {  // -1337 > 1338 == 0 no
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(-1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1338, &num2);
  ck_assert_int_eq(0, s21_is_greater(num1, num2));
}
END_TEST

START_TEST(is_greater_min_num2) {  // 1337 > -1338 == 1 yes
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(-1338, &num2);
  ck_assert_int_eq(1, s21_is_greater(num1, num2));
}
END_TEST

START_TEST(is_greater_min_both) {  // -1337 > -1338 == 1 yes
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(-1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(-1338, &num2);
  ck_assert_int_eq(1, s21_is_greater(num1, num2));
}
END_TEST

// === is_less_or_equal === //
START_TEST(is_less_or_equal_num1_less) {  // 1337 <= 1338 == 1 yes
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1338, &num2);
  ck_assert_int_eq(1, s21_is_less_or_equal(num1, num2));
}
END_TEST

START_TEST(is_less_or_equal_num2_less) {  // 1338 <= 1337 == 0 no
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1338, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1337, &num2);
  ck_assert_int_eq(0, s21_is_less_or_equal(num1, num2));
}
END_TEST

START_TEST(is_less_or_equal_both_equal) {  // 1337 <= 1337 == 1 yes
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1337, &num2);
  ck_assert_int_eq(1, s21_is_less_or_equal(num1, num2));
}
END_TEST

// === is_greater_or_equal === //
START_TEST(is_greater_or_equal_num1_less) {  // 1337 >= 1338 == 0 no
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1338, &num2);
  ck_assert_int_eq(0, s21_is_greater_or_equal(num1, num2));
}
END_TEST

START_TEST(is_greater_or_equal_num2_less) {  // 1338 >= 1337 == 1 yes
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1338, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1337, &num2);
  ck_assert_int_eq(1, s21_is_greater_or_equal(num1, num2));
}
END_TEST

START_TEST(is_greater_or_equal_both_equal) {  // 1337 >= 1337 == 1 yes
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1337, &num2);
  ck_assert_int_eq(1, s21_is_greater_or_equal(num1, num2));
}
END_TEST

// === is_equal === //
START_TEST(is_equal_true) {  // 1337 = 1337 == 1 yes
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1337, &num2);
  ck_assert_int_eq(1, s21_is_equal(num1, num2));
}
END_TEST

START_TEST(is_equal_false) {  // 1337 = 1338 == 0 no
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1338, &num2);
  ck_assert_int_eq(0, s21_is_equal(num1, num2));
}
END_TEST

START_TEST(is_equal_min_num1) {  // 1337 = 1338 == 0 no
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(-1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1338, &num2);
  ck_assert_int_eq(0, s21_is_equal(num1, num2));
}
END_TEST

START_TEST(is_equal_min_num2) {  // 1337 = 1338 == 0 no
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(-1338, &num2);
  ck_assert_int_eq(0, s21_is_equal(num1, num2));
}
END_TEST

START_TEST(is_equal_min_both) {  // 1337 = 1338 == 0 no
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(-1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(-1338, &num2);
  ck_assert_int_eq(0, s21_is_equal(num1, num2));
}
END_TEST

// === is_not_equal === //
START_TEST(is_not_equal_true) {  // 1337 != 1338 == 1 yes
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1338, &num2);
  ck_assert_int_eq(1, s21_is_not_equal(num1, num2));
}
END_TEST

START_TEST(is_not_equal_false) {  // 1337 != 1337 == 0 no
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1337, &num2);
  ck_assert_int_eq(0, s21_is_not_equal(num1, num2));
}
END_TEST
// END OF baggmela tests

// //================= converter functions tests =================
// from_int_to_decimal
START_TEST(part1_conv_int) {
  int a = 123123;
  s21_decimal result = {0};
  s21_from_int_to_decimal(a, &result);
  ck_assert_uint_eq(result.bits[0], a);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_pow(result), 0);
  a = 2147483647;
  s21_from_int_to_decimal(a, &result);
  ck_assert_uint_eq(result.bits[0], a);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_pow(result), 0);
  a = -2147483648;
  s21_from_int_to_decimal(a, &result);
  ck_assert_uint_eq(result.bits[0], 2147483648);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_pow(result), 0);

  a = 0;
  s21_decimal temp;
  init_decimal(&temp);
  temp.bits[0] = 1U;
  set_sign(&temp, 1);
  s21_from_decimal_to_int(temp, &a);
  ck_assert_int_eq(a, -1);

  a = 0;
  init_decimal(&temp);
  temp.bits[0] = 1U;
  temp.bits[3] = 0;
  s21_from_decimal_to_int(temp, &a);
  ck_assert_int_eq(a, 1);

  a = 0;
  init_decimal(&temp);
  temp.bits[0] = 123;
  temp.bits[1] = 123;
  int res = 0;
  res = s21_from_decimal_to_int(temp, &a);
  ck_assert_uint_eq(res, 1);
}
END_TEST

// FLOAT

START_TEST(part1_conv_float) {
  s21_decimal temp;
  init_decimal(&temp);
  float a = 0.0;
  s21_from_float_to_decimal(a, &temp);
  ck_assert_int_eq(temp.bits[0], 0);
  ck_assert_int_eq(get_sign(temp), 0);

  init_decimal(&temp);
  a = 20.0;
  s21_from_float_to_decimal(a, &temp);
  ck_assert_int_eq(temp.bits[0], 20);
  ck_assert_int_eq(get_sign(temp), 0);
  ck_assert_int_eq(get_pow(temp), 0);

  init_decimal(&temp);
  a = -20.0;
  s21_from_float_to_decimal(a, &temp);
  ck_assert_int_eq(temp.bits[0], 20);
  ck_assert_int_eq(get_sign(temp), 1);
  ck_assert_int_eq(get_pow(temp), 0);

  init_decimal(&temp);
  a = 0.0 / 0.0;
  int res = s21_from_float_to_decimal(a, &temp);
  ck_assert_int_eq(res, 1);

  init_decimal(&temp);
  a = 1.0 / 0.0;
  res = 0;
  res = s21_from_float_to_decimal(a, &temp);
  ck_assert_int_eq(res, 1);

  init_decimal(&temp);
  a = -1.0 / 0.0;
  res = 0;
  res = s21_from_float_to_decimal(a, &temp);
  ck_assert_int_eq(res, 1);

  init_decimal(&temp);
  a = 0;
  temp.bits[0] = 45;
  set_pow(temp, &temp, 1);
  s21_from_decimal_to_float(temp, &a);
  ck_assert_float_eq(a, 4.5);

  init_decimal(&temp);
  a = 0;
  temp.bits[0] = 45;
  set_pow(temp, &temp, 1);
  set_sign(&temp, 1);
  s21_from_decimal_to_float(temp, &a);
  ck_assert_float_eq(a, -4.5);
}
END_TEST

//================= other functions tests =================
// negate =================>
START_TEST(part1_negate_zero) {
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  s21_negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(part2_negate_zero_signed) {
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  set_sign(&value_1, 1);
  s21_negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(part3_negate_one) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{1, 0, 0, 0}};
  // set_sign(&test, 1);
  s21_negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(part4_negate_one_signed) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{1, 0, 0, 0}};
  set_sign(&value_1, 1);
  s21_negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(part5_negate_num) {
  s21_decimal value_1 = {{422142, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{422142}};
  s21_negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(part6_negate_num_signed) {
  s21_decimal value_1 = {{422142, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{422142, 0, 0, 0}};
  set_sign(&value_1, 1);
  s21_negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(part7_negate_pow) {
  s21_decimal value_1 = {{422142, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{422142, 0, 0, 0}};
  set_pow(value_1, &value_1, 2);
  s21_negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_pow(result), 2);
}
END_TEST

START_TEST(part8_negate_pow_signed) {
  s21_decimal value_1 = {{422142, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{422142, 0, 0, 0}};
  set_sign(&value_1, 1);
  set_pow(value_1, &value_1, 2);
  s21_negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_pow(result), 2);
}
END_TEST

// truncate =================>
START_TEST(part1_truncate_zero) {
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_pow(result), 0);

  set_sign(&value_1, 1);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_pow(result), 0);
}
END_TEST

START_TEST(part2_truncate_zero_pow) {
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  test.bits[0] = 0;
  set_pow(value_1, &value_1, 21);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_pow(result), 0);

  set_sign(&value_1, 1);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_pow(result), 0);
}
END_TEST

START_TEST(part3_truncate_one) {
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 1;
  test.bits[0] = 1;
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_pow(result), 0);

  set_sign(&value_1, 1);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_pow(result), 0);
}
END_TEST

START_TEST(part4_truncate_num1) {
  s21_decimal value_1 = {{422142, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{422142, 0, 0, 0}};
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_pow(result), 0);

  set_sign(&value_1, 1);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_pow(result), 0);
}
END_TEST

START_TEST(part5_truncate_num2) {
  s21_decimal value_1 = {{422142, 0, 422142, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{422142, 0, 422142, 0}};
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[2], test.bits[2]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_pow(result), 0);

  set_sign(&value_1, 1);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[2], test.bits[2]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_pow(result), 0);
}
END_TEST

START_TEST(part6_truncate_pow1) {
  s21_decimal value_1 = {{422142, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{422, 0, 0, 0}};
  set_pow(value_1, &value_1, 3);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_pow(result), 0);

  set_sign(&value_1, 1);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_pow(result), 0);
}
END_TEST

START_TEST(part7_truncate_pow2) {
  s21_decimal value_1 = {{422142, 422142, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{609885778, 422, 0, 0}};
  set_pow(value_1, &value_1, 3);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_pow(result), 0);

  set_sign(&value_1, 1);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_pow(result), 0);
}
END_TEST

START_TEST(part8_truncate_pow3) {
  s21_decimal value_1 = {{422142, 422142, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{181308, 0, 0, 0}};
  set_pow(value_1, &value_1, 10);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_pow(result), 0);

  set_sign(&value_1, 1);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_pow(result), 0);
}
END_TEST

// floor =================>
START_TEST(part1_floor_zero) {
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  set_pow(value_1, &value_1, 1);
  s21_floor(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_pow(result), 0);

  set_sign(&value_1, 1);
  s21_floor(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_pow(result), 0);
}
END_TEST

START_TEST(part2_floor_one) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{1, 0, 0, 0}};
  s21_floor(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_pow(result), 0);

  set_sign(&value_1, 1);
  s21_floor(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_pow(result), 0);
}
END_TEST

START_TEST(part3_floor_num) {
  s21_decimal value_1 = {{422142, 0, 422142, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{422142, 0, 422142, 0}};
  s21_floor(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[2], test.bits[2]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_pow(result), 0);

  set_sign(&value_1, 1);
  s21_floor(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[2], test.bits[2]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_pow(result), 0);
}
END_TEST

START_TEST(part4_floor_pow1) {
  s21_decimal value_1 = {{422142, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{422, 0, 0, 0}};
  set_pow(value_1, &value_1, 3);
  s21_floor(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_pow(result), 0);

  test.bits[0] = 423;
  set_sign(&value_1, 1);
  s21_floor(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_pow(result), 0);
}
END_TEST

START_TEST(part5_floor_pow2) {
  s21_decimal value_1 = {{422142, 422142, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{609885778, 422, 0, 0}};
  set_pow(value_1, &value_1, 3);
  s21_floor(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_pow(result), 0);

  test.bits[0] = 609885779;
  set_sign(&value_1, 1);
  s21_floor(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_pow(result), 0);
}
END_TEST

START_TEST(part6_floor_pow3) {
  s21_decimal value_1 = {{422942, 422142, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{181308, 422, 0, 0}};
  set_pow(value_1, &value_1, 10);
  s21_floor(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_pow(result), 0);

  test.bits[0] = 181309;
  set_sign(&value_1, 1);
  s21_floor(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_pow(result), 0);
}
END_TEST

// round =================>
START_TEST(part1_round_zero) {
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  set_pow(value_1, &value_1, 1);
  s21_round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_pow(result), 0);

  set_sign(&value_1, 1);
  s21_round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_pow(result), 0);
}
END_TEST

START_TEST(part2_round_one) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{1, 0, 0, 0}};
  s21_round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_pow(result), 0);

  set_sign(&value_1, 1);
  s21_round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_pow(result), 0);
}
END_TEST

START_TEST(part3_round_num) {
  s21_decimal value_1 = {{422142, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{422142, 0, 0, 0}};
  s21_round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_pow(result), 0);

  set_sign(&value_1, 1);
  s21_round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_pow(result), 0);
}
END_TEST

START_TEST(part4_round_pow1) {
  s21_decimal value_1 = {{4221425, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{422143, 0, 0, 0}};
  set_pow(value_1, &value_1, 1);
  s21_round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_pow(result), 0);

  set_sign(&value_1, 1);
  s21_round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_pow(result), 0);
}
END_TEST

START_TEST(part5_round_pow2) {
  s21_decimal value_1 = {{4221424, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{422142, 0, 0, 0}};
  set_pow(value_1, &value_1, 1);
  s21_round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_pow(result), 0);

  set_sign(&value_1, 1);
  s21_round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_pow(result), 0);
}
END_TEST

START_TEST(part6_round_pow3) {
  s21_decimal value_1 = {{4221426, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{422143, 0, 0, 0}};
  set_pow(value_1, &value_1, 1);
  s21_round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_pow(result), 0);

  set_sign(&value_1, 1);
  s21_round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_pow(result), 0);
}
END_TEST

START_TEST(part7_round_pow4) {
  s21_decimal value_1 = {{422142, 422142, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{609885778, 422, 0, 0}};
  set_pow(value_1, &value_1, 3);
  s21_round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_pow(result), 0);

  set_sign(&value_1, 1);
  s21_round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_pow(result), 0);
}
END_TEST

START_TEST(part8_round_pow5) {
  s21_decimal value_1 = {{420521, 422142, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{609885777, 422, 0, 0}};
  set_pow(value_1, &value_1, 3);
  s21_round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_pow(result), 0);

  set_sign(&value_1, 1);
  s21_round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_pow(result), 0);
}
END_TEST

// dec_output(value_1); printf("\n"); dec_output(test); printf("\n");
// dec_output(result); printf("\n"); dec_output(test); printf("\n");
// printf("\n%d %d\n", result.bits[0], test.bits[0]);

//================= SUITES =================
Suite *arithmetic_test_suite() {
  Suite *s = suite_create("arithmetic_test_suite");
  TCase *tc_add = tcase_create("tc_add");
  TCase *tc_sub = tcase_create("tc_sub");
  TCase *tc_mult = tcase_create("tc_mult");
  TCase *tc_div = tcase_create("tc_div");
  // TCase *tc_div = tcase_create("tc_div");

  tcase_add_test(tc_add, part1_add_normal);
  tcase_add_test(tc_add, part1_add_both_neg);
  tcase_add_test(tc_add, part1_add_error);
  tcase_add_test(tc_add, part1_add_one_sign);
  tcase_add_test(tc_add, part1_add_one_greater);

  tcase_add_test(tc_sub, part1_sub_normal);
  tcase_add_test(tc_sub, part1_sub_inf);
  tcase_add_test(tc_sub, part1_sub_one_sign);
  tcase_add_test(tc_sub, part1_sub_two_sign);

  tcase_add_test(tc_mult, part1_mult_value_1_is_one);
  tcase_add_test(tc_mult, part1_mult_value_2_is_one);
  tcase_add_test(tc_mult, part1_mult_value_1_is_zero);
  tcase_add_test(tc_mult, part1_mult_value_2_is_zero);
  tcase_add_test(tc_mult, part1_mult_max);
  tcase_add_test(tc_mult, part1_mult_big_power);
  tcase_add_test(tc_mult, part1_mult_big_over);
  tcase_add_test(tc_mult, part1_mult_big_negative_over);
  tcase_add_test(tc_mult, part1_mult_value_1_is_minus);
  tcase_add_test(tc_mult, part1_mult_value_2_is_minus);
  tcase_add_test(tc_mult, part1_mult_value_1_is_zero_minus);
  tcase_add_test(tc_mult, part1_mult_value_2_is_zero_minus);
  tcase_add_test(tc_mult, part1_mult_value_1_2_is_minus);

  tcase_add_test(tc_div, div_0);
  tcase_add_test(tc_div, div_1);
  tcase_add_test(tc_div, div_2);
  tcase_add_test(tc_div, div_3);
  tcase_add_test(tc_div, div_4);
  tcase_add_test(tc_div, div_5);
  tcase_add_test(tc_div, div_6);
  tcase_add_test(tc_div, div_7);
  tcase_add_test(tc_div, div_8);

  suite_add_tcase(s, tc_add);
  suite_add_tcase(s, tc_sub);
  suite_add_tcase(s, tc_mult);
  suite_add_tcase(s, tc_div);

  return s;
}

Suite *comparison_test_suite(void) {
  Suite *s = suite_create("comparison_test_suite");

  TCase *is_less = tcase_create("IS_LESS");
  tcase_add_test(is_less, is_less_plus_both);
  tcase_add_test(is_less, is_less_min_num1);
  tcase_add_test(is_less, is_less_min_num2);
  tcase_add_test(is_less, is_less_min_both);
  suite_add_tcase(s, is_less);

  TCase *is_greater = tcase_create("IS_GREATER");
  tcase_add_test(is_greater, is_greater_plus_both);
  tcase_add_test(is_greater, is_greater_min_num1);
  tcase_add_test(is_greater, is_greater_min_num2);
  tcase_add_test(is_greater, is_greater_min_both);
  suite_add_tcase(s, is_greater);

  TCase *is_less_or_equal = tcase_create("IS_LESS_OR_EQUAL");
  tcase_add_test(is_less_or_equal, is_less_or_equal_num1_less);
  tcase_add_test(is_less_or_equal, is_less_or_equal_num2_less);
  tcase_add_test(is_less_or_equal, is_less_or_equal_both_equal);
  suite_add_tcase(s, is_less_or_equal);

  TCase *is_greater_or_equal = tcase_create("IS_GREATER_OR_EQUAL");
  tcase_add_test(is_greater_or_equal, is_greater_or_equal_num1_less);
  tcase_add_test(is_greater_or_equal, is_greater_or_equal_num2_less);
  tcase_add_test(is_greater_or_equal, is_greater_or_equal_both_equal);
  suite_add_tcase(s, is_greater_or_equal);

  TCase *is_equal = tcase_create("IS_EQUAL");
  tcase_add_test(is_equal, is_equal_false);
  tcase_add_test(is_equal, is_equal_true);
  tcase_add_test(is_equal, is_equal_min_num1);
  tcase_add_test(is_equal, is_equal_min_num2);
  tcase_add_test(is_equal, is_equal_min_both);
  suite_add_tcase(s, is_equal);

  TCase *is_not_equal = tcase_create("IS_NOT_EQUAL");
  tcase_add_test(is_not_equal, is_not_equal_false);
  tcase_add_test(is_not_equal, is_not_equal_true);
  suite_add_tcase(s, is_not_equal);

  return s;
}

Suite *converter_test_suite() {
  Suite *s = suite_create("converter_test_suite");

  TCase *tc_int = tcase_create("tc_int");
  TCase *tc_float = tcase_create("tc_float");

  tcase_add_test(tc_int, part1_conv_int);
  tcase_add_test(tc_float, part1_conv_float);

  suite_add_tcase(s, tc_int);
  suite_add_tcase(s, tc_float);

  return s;
}

Suite *other_test_suite() {
  Suite *s = suite_create("other_test_suite");

  TCase *tc_negate = tcase_create("tc_negate");
  TCase *tc_truncate = tcase_create("tc_truncate");
  TCase *tc_floor = tcase_create("tc_floor");
  TCase *tc_round = tcase_create("tc_round");

  tcase_add_test(tc_negate, part1_negate_zero);
  tcase_add_test(tc_negate, part2_negate_zero_signed);
  tcase_add_test(tc_negate, part3_negate_one);
  tcase_add_test(tc_negate, part4_negate_one_signed);
  tcase_add_test(tc_negate, part5_negate_num);
  tcase_add_test(tc_negate, part6_negate_num_signed);
  tcase_add_test(tc_negate, part7_negate_pow);
  tcase_add_test(tc_negate, part8_negate_pow_signed);

  tcase_add_test(tc_truncate, part1_truncate_zero);
  tcase_add_test(tc_truncate, part2_truncate_zero_pow);
  tcase_add_test(tc_truncate, part3_truncate_one);
  tcase_add_test(tc_truncate, part4_truncate_num1);
  tcase_add_test(tc_truncate, part5_truncate_num2);
  tcase_add_test(tc_truncate, part6_truncate_pow1);
  tcase_add_test(tc_truncate, part7_truncate_pow2);
  tcase_add_test(tc_truncate, part8_truncate_pow3);

  tcase_add_test(tc_floor, part1_floor_zero);
  tcase_add_test(tc_floor, part2_floor_one);
  tcase_add_test(tc_floor, part3_floor_num);
  tcase_add_test(tc_floor, part4_floor_pow1);
  tcase_add_test(tc_floor, part5_floor_pow2);
  tcase_add_test(tc_floor, part6_floor_pow3);

  tcase_add_test(tc_round, part1_round_zero);
  tcase_add_test(tc_round, part2_round_one);
  tcase_add_test(tc_round, part3_round_num);
  tcase_add_test(tc_round, part4_round_pow1);
  tcase_add_test(tc_round, part5_round_pow2);
  tcase_add_test(tc_round, part6_round_pow3);
  tcase_add_test(tc_round, part7_round_pow4);
  tcase_add_test(tc_round, part8_round_pow5);

  suite_add_tcase(s, tc_negate);
  suite_add_tcase(s, tc_floor);
  suite_add_tcase(s, tc_round);
  suite_add_tcase(s, tc_truncate);

  return s;
}

int main() {
  printf("================= TESTING =================\n\n");
  Suite *s_1 = arithmetic_test_suite();
  Suite *s_2 = comparison_test_suite();
  Suite *s_3 = converter_test_suite();
  Suite *s_4 = other_test_suite();
  run_test(s_1);
  run_test(s_2);
  run_test(s_3);
  run_test(s_4);
  printf("================= END =================\n");
  return 0;
}