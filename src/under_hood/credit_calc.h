#ifndef CREDIT_CALC_H
#define CREDIT_CALC_H

#include "../smart_calc.h"

long double monthly_payment_annuity(long double credit_sum, double term,
                                    long double tax_rate);
long double total_payment_annuity(long double monthly_payment_ann, double term);
long double monthly_payment_diff(long double credit_sum, double term);
long double total_payment_diff(long double credit_sum, double term,
                               long double tax_rate);
long double overpayment(long double credit_sum, long double total_payment);
double year_to_month(double year_term);

#endif  // !CREDIT_CALC_H
