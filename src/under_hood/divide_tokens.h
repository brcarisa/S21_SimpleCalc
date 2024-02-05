#ifndef DIVIDE_TOKENS_H
#define DIVIDE_TOKENS_H

#include "../smart_calc.h"

void replace_x_to_value(char *str, long double value);
void add_end_line(char *str);
void unary_plus_or_minus_pars(char *str);
int func_processing(char *str);
char *token_separator(char *str);

#endif  // !DIVIDE_TOKENS_H
