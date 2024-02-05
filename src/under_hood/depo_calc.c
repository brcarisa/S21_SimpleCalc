#include "depo_calc.h"

long double get_tax_sum(long double earned_sum, long double tax_rate) {
  return (earned_sum * tax_rate) / 100;
}

long double sum_after_tax(long double dep_sum, long double earned_sum,
                          long double tax_sum) {
  return dep_sum + earned_sum - tax_sum;
}

long double get_total_profit(long double *deposit_sum, long double term,
                             long double percent_rate, int timing,
                             bool is_capitalisation, long double additions,
                             long double withdraws) {
  long double earned_sum = 0;
  int period = timing == MONTH ? 12 : 1;
  additions = timing == MONTH ? additions : additions * 12;
  withdraws = timing == MONTH ? withdraws : withdraws * 12;
  for (int i = 0; (long double)i < term; i++) {
    long double earnings = 0;
    if (timing == MONTH) {
      earnings = *deposit_sum * percent_rate / 100 / period;
    }
    if (timing == YEAR) {
      if (i % 11 == 0 && i != 0) {
        earnings = *deposit_sum * percent_rate / 100 / period;
      }
    }
    *deposit_sum = *deposit_sum - withdraws;
    *deposit_sum = *deposit_sum + additions;
    if (is_capitalisation) {
      *deposit_sum = *deposit_sum + earnings;
    }
    earned_sum = earned_sum + earnings;
  }
  return earned_sum;
}
