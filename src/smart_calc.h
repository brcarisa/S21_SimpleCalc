#ifndef SMART_CALC_H
#define SMART_CALCL_H

#define MAX_LEN 255
#define PERMITTED_SYMBOLS "1234567890()+-*%%/^cstalx."
#define NUMBERS "1234567890"
#define NUMBERS_AND_DOT "1234567890."
#define NUMBERS_AND_DOT_AND_X "1234567890.x"
#define OPERANDS "1234567890cstalx.("
#define OPERATORS "+-*%%/^"
#define BRACKETS "()"
#define FUNCTIONS "cstal"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "under_hood/calc_operations.h"
#include "under_hood/credit_calc.h"
#include "under_hood/depo_calc.h"
#include "under_hood/divide_tokens.h"
#include "under_hood/from_infix_to_polish.h"
#include "under_hood/stack_elements.h"
#include "under_hood/valid_input.h"

void mod_to_percent(char *str, const char *old_substring,
                    const char *new_substring);
int calculate_str_api_with_x(const char *str, long double x, long double *res);
int calculate_str_api(const char *str, long double *res);

#endif  // !SMART_CALC_H
