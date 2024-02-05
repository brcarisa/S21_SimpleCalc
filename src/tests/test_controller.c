#include "test_controller.h"

START_TEST(api_calc_opt_1) {
  char *input = "5+10+97+0*log(12)";
  long double result = 0;
  calculate_str_api(input, &result);
  ck_assert_ldouble_eq(result, 112.000000);
}
END_TEST

START_TEST(api_calc_opt_2) {
  char *input = "2^2^3";
  long double result = 0;
  calculate_str_api(input, &result);
  ck_assert_ldouble_eq(result, 256.000000);
}
END_TEST

START_TEST(api_calc_opt_3) {
  char *input = "acos(15)+asin(30)/(atan(2)*sqrt(9))";
  long double result = 0;
  calculate_str_api(input, &result);
  int test_res = fabsl(result - (-0.308071)) < 1e-6 ? OK : FAILURE;
  ck_assert_ldouble_eq(test_res, OK);
}
END_TEST

START_TEST(api_calc_opt_4) {
  char *input = "cos(3-1)/sin(5)*tan(1)^1";
  long double result = 0;
  calculate_str_api(input, &result);
  int test_res = fabsl(result - (-0.420225)) < 1e-6 ? OK : FAILURE;
  ck_assert_ldouble_eq(test_res, OK);
}
END_TEST

START_TEST(api_calc_opt_5) {
  char *input =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  long double result = 0;
  calculate_str_api(input, &result);
  int test_res = fabsl(result - (-30.0722)) < 1e-4 ? OK : FAILURE;
  ck_assert_ldouble_eq(test_res, OK);
}
END_TEST

START_TEST(api_calc_opt_6) {
  char *input = "cos(3-1)/sin(5)*tan(1)^1";
  long double result = 0;
  calculate_str_api(input, &result);
  int test_res = fabsl(result - (-0.420225)) < 1e-6 ? OK : FAILURE;
  ck_assert_ldouble_eq(test_res, OK);
}
END_TEST

START_TEST(api_calc_opt_7) {
  char *input = "ln(10)-(-log(2))";
  long double result = 0;
  calculate_str_api(input, &result);
  int test_res = fabsl(result - (2.33224)) < 1e-4 ? OK : FAILURE;
  ck_assert_ldouble_eq(test_res, OK);
}
END_TEST

START_TEST(api_calc_opt_8) {
  char *input = "acos(6)+asin(9)/atan(0.5)+sqrt(0.1)";
  long double result = 0;
  calculate_str_api(input, &result);
  int test_res = fabsl(result - (0.858795)) < 1e-6 ? OK : FAILURE;
  ck_assert_ldouble_eq(test_res, OK);
}
END_TEST

START_TEST(api_calc_opt_9) {
  char *input = "irina_kairatovna";
  long double result = 0;
  int res_test = calculate_str_api(input, &result);
  ck_assert_int_eq(res_test, FAILURE);
}
END_TEST

START_TEST(api_calc_opt_10) {
  char *input = "(cos(()))";
  long double result = 0;
  int res_test = calculate_str_api(input, &result);
  ck_assert_int_eq(res_test, FAILURE);
}
END_TEST

START_TEST(api_calc_with_x_opt_1) {
  char *input = "x*x*x";
  long double result = 0;
  calculate_str_api_with_x(input, -2, &result);
  ck_assert_ldouble_eq(result, -8.000000);
}
END_TEST

START_TEST(api_calc_with_x_opt_2) {
  char *input = "cos(3-1)/sin(5)*tan(1)^x";
  long double result = 0;
  calculate_str_api_with_x(input, -2, &result);
  int test_res = fabsl(result - (-0.420225)) < 1e-4 ? OK : FAILURE;
  ck_assert_int_eq(test_res, OK);
}
END_TEST

START_TEST(api_calc_with_x_opt_3) {
  char *input = "acos(6)+asin(9)/atan(0.5*x)+sqrt(0.1)";
  long double result = 0;
  calculate_str_api_with_x(input, -2, &result);
  int test_res = fabsl(result - (0.754673)) < 1e-4 ? OK : FAILURE;
  ck_assert_int_eq(test_res, OK);
}
END_TEST

START_TEST(api_calc_with_x_opt_4) {
  char *input = "ln(10)-(-log(2*x*x))";
  long double result = 0;
  calculate_str_api_with_x(input, -2, &result);
  int test_res = fabsl(result - (2.389046)) < 1e-4 ? OK : FAILURE;
  ck_assert_int_eq(test_res, OK);
}
END_TEST

START_TEST(api_calc_with_x_opt_5) {
  char *input = "ln(10*x*x)-x*(-log(2))";
  long double result = 0;
  calculate_str_api_with_x(input, -2, &result);
  int test_res = fabsl(result - (3.673714)) < 1e-4 ? OK : FAILURE;
  ck_assert_int_eq(test_res, OK);
}
END_TEST

START_TEST(api_calc_with_x_opt_6) {
  char *input = "12031997+05101997";
  long double result = 0;
  calculate_str_api_with_x(input, -2, &result);
  ck_assert_ldouble_eq(result, 17133994.000000);
}
END_TEST

START_TEST(api_calc_with_x_opt_7) {
  char *input = "x+5";
  long double result = 0;
  calculate_str_api_with_x(input, -2, &result);
  int test_res = fabsl(result - (3)) < 1e-4 ? OK : FAILURE;
  ck_assert_int_eq(test_res, OK);
}
END_TEST

START_TEST(api_calc_with_x_opt_8) {
  char *input = "1000000-x";
  long double result = 0;
  calculate_str_api_with_x(input, -2, &result);
  ck_assert_ldouble_eq(result, 1000002.000000);
}
END_TEST

START_TEST(api_calc_with_x_opt_9) {
  char *input = "sin(130)+x-x*x*(x)";
  long double result = 0;
  calculate_str_api_with_x(input, -2, &result);
  int test_res = fabsl(result - (-0.790433)) < 1e-4 ? OK : FAILURE;
  ck_assert_int_eq(test_res, OK);
}
END_TEST

START_TEST(api_calc_with_x_opt_10) {
  char *input = "sin)";
  long double result = 0;
  int test_res = calculate_str_api_with_x(input, -2, &result);
  ck_assert_int_eq(test_res, FAILURE);
}
END_TEST

START_TEST(api_calc_with_x_opt_11) {
  char *input = "vse_budet_horosho_dorogoi";
  long double result = 0;
  int test_res = calculate_str_api_with_x(input, -2, &result);
  ck_assert_int_eq(test_res, FAILURE);
}
END_TEST

START_TEST(api_calc_with_x_opt_12) {
  char *input = "chukka dagi makasin mne 8 let ya assasin";
  long double result = 0;
  int test_res = calculate_str_api_with_x(input, -2, &result);
  ck_assert_int_eq(test_res, FAILURE);
}
END_TEST

Suite *api_calc_suit(void) {
  Suite *suite = suite_create("api_calc");
  TCase *tc_core = tcase_create("core_of_api_calc");
  tcase_add_test(tc_core, api_calc_opt_1);
  tcase_add_test(tc_core, api_calc_opt_2);
  tcase_add_test(tc_core, api_calc_opt_3);
  tcase_add_test(tc_core, api_calc_opt_4);
  tcase_add_test(tc_core, api_calc_opt_5);
  tcase_add_test(tc_core, api_calc_opt_6);
  tcase_add_test(tc_core, api_calc_opt_7);
  tcase_add_test(tc_core, api_calc_opt_8);
  tcase_add_test(tc_core, api_calc_opt_9);
  tcase_add_test(tc_core, api_calc_opt_10);
  suite_add_tcase(suite, tc_core);

  return suite;
}

Suite *api_calc_with_x_suit(void) {
  Suite *suite = suite_create("api_calc_with_x");
  TCase *tc_core = tcase_create("core_of_api_calc_with_x");
  tcase_add_test(tc_core, api_calc_with_x_opt_1);
  tcase_add_test(tc_core, api_calc_with_x_opt_2);
  tcase_add_test(tc_core, api_calc_with_x_opt_3);
  tcase_add_test(tc_core, api_calc_with_x_opt_4);
  tcase_add_test(tc_core, api_calc_with_x_opt_5);
  tcase_add_test(tc_core, api_calc_with_x_opt_6);
  tcase_add_test(tc_core, api_calc_with_x_opt_7);
  tcase_add_test(tc_core, api_calc_with_x_opt_8);
  tcase_add_test(tc_core, api_calc_with_x_opt_9);
  tcase_add_test(tc_core, api_calc_with_x_opt_10);
  tcase_add_test(tc_core, api_calc_with_x_opt_11);
  tcase_add_test(tc_core, api_calc_with_x_opt_12);
  suite_add_tcase(suite, tc_core);

  return suite;
}

void s21_suit_execution(Suite *suite, int *failed_count, char *suite_name) {
  SRunner *suite_runner = srunner_create(suite);
  srunner_set_log(suite_runner, suite_name);
  srunner_run_all(suite_runner, CK_NORMAL);
  *failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
}

int main(void) {
  int failed_count = 0;

  s21_suit_execution(api_calc_suit(), &failed_count,
                     "tests/log/api_calc_tests.log");
  s21_suit_execution(api_calc_with_x_suit(), &failed_count,
                     "tests/log/api_calc_with_x_tests.log");

  return failed_count == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}