#ifndef CALC_OPERATIONS_H
#define CALC_OPERATIONS_H

#include "../smart_calc.h"
#include "stack_elements.h"

bool functions_calc(ld_stack_t *ld_stack, long double *res, char *function);
bool calc_ld_stack(ld_stack_t *ld_stack, long double *res, int sign);
bool calc_operations(ld_stack_t *ld_stack, char *token, long double *result);
long double result_calculate(char *str);

#endif  // !CALC_OPERATIONS_H
