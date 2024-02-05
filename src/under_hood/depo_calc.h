#ifndef DEPO_CALC_H
#define DEPO_CALC_H

#include "../smart_calc.h"

enum TIMING { MONTH, YEAR };

long double get_total_profit(long double *deposit_sum, long double term,
                             long double percent_rate, int timing,
                             bool is_capitalisation, long double replenishments,
                             long double withdraws);
long double sum_after_tax(long double dep_sum, long double earned_sum,
                          long double tax_sum);
long double get_tax_sum(long double earned_sum, long double tax_rate);

#endif  // !DEPO_CALC_H
