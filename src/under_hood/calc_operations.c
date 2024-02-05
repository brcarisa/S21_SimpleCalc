#include "calc_operations.h"

bool functions_calc(ld_stack_t *ld_stack, long double *res, char *function) {
  if (ld_stack == NULL || res == NULL || function == NULL) {
    return false;
  }
  long double value = pop_ld(ld_stack);
  if (strstr(function, "cos")) {
    *res = cosl(value);
  } else if (strstr(function, "sin")) {
    *res = sinl(value);
  } else if (strstr(function, "tan")) {
    *res = tanl(value);
  } else if (strstr(function, "acos")) {
    *res = acosl(value);
  } else if (strstr(function, "asin")) {
    *res = asinl(value);
  } else if (strstr(function, "atan")) {
    *res = atanl(value);
  } else if (strstr(function, "sqrt")) {
    *res = sqrtl(value);
  } else if (strstr(function, "ln")) {
    *res = logl(value);
  } else if (strstr(function, "log")) {
    *res = log10l(value);
  }
  return isnan(*res) == 0 ? true : false;
}

bool calc_ld_stack(ld_stack_t *ld_stack, long double *res, int sign) {
  if (ld_stack == NULL || res == NULL) {
    return false;
  }
  long double val_1 = pop_ld(ld_stack);
  long double val_2 = pop_ld(ld_stack);

  if (sign == '+') {
    *res = val_2 + val_1;
  } else if (sign == '-') {
    *res = val_2 - val_1;
  } else if (sign == '*') {
    *res = val_2 * val_1;
  } else if (sign == '/') {
    *res = val_2 / val_1;
  } else if (sign == '^') {
    *res = powl(val_2, val_1);
  } else if (sign == '%') {
    *res = fmodl(val_2, val_1);
  }
  return isnan(*res) == 0 ? true : false;
}

bool calc_operations(ld_stack_t *ld_stack, char *token, long double *result) {
  if (ld_stack == NULL || token == NULL || result == NULL) {
    return false;
  }
  bool is_success = true;
  if (strchr(NUMBERS_AND_DOT, (int)*token)) {
    push_ld(ld_stack, strtold(token, &token));
  } else if (strchr(OPERATORS, (int)*token)) {
    long double res = 0;
    is_success = calc_ld_stack(ld_stack, &res, (int)*token);
    if (is_success) {
      push_ld(ld_stack, res);
    }
  } else if (strchr("~", (int)*token)) {
    push_ld(ld_stack, 0 - pop_ld(ld_stack));
  } else if (strchr("p", (int)*token)) {
    push_ld(ld_stack, 0 + pop_ld(ld_stack));
  } else {
    long double res = 0;
    is_success = functions_calc(ld_stack, &res, token);
    if (is_success) {
      push_ld(ld_stack, res);
    }
  }
  return is_success;
}

long double result_calculate(char *str) {
  if (str == NULL) {
    return 0;
  }
  char buff[MAX_LEN + 1] = {'\0'};
  strncpy(buff, str, MAX_LEN);
  long double res = 0;
  bool is_error = false;
  ld_stack_t *ld_stack = init_ld_stack();
  if (ld_stack != NULL) {
    char *token = strtok(buff, " ");
    while (token != NULL && !is_error) {
      is_error = !calc_operations(ld_stack, token, &res);
      token = strtok(NULL, " ");
    }
    res = pop_ld(ld_stack);
    remove_ld_stack(ld_stack);
    free(ld_stack);
    ld_stack = NULL;
  } else {
    is_error = true;
  }
  return is_error == 0 ? res : NAN;
}