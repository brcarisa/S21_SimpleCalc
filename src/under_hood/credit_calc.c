#include "credit_calc.h"
//Расчет аннуитетного ежемесячного платежа 
long double monthly_payment_annuity(long double credit_sum, double term,
                                    long double tax_rate) {
  long double month_tax_rate_dec = tax_rate / 12 / 100;
  long double monthly_payment_ann =
      credit_sum * (month_tax_rate_dec * powl(1 + month_tax_rate_dec, term)) /
      (powl(1 + month_tax_rate_dec, term) - 1);
  return monthly_payment_ann;
}
//Расчет полного аннуитетного платежа
long double total_payment_annuity(long double monthly_payment_ann,
                                  double term) {
  return monthly_payment_ann * term;
}

long double monthly_payment_diff(long double total_payment, double term) {
  return total_payment / term;
}

long double total_payment_diff(long double credit_sum, double term,
                               long double tax_rate) {
  long double month_tax_rate_dec = tax_rate / 12 / 100;
  long double month_payment_diff = monthly_payment_diff(credit_sum, term);
  long double total_payment = 0;
  for (int month = 0; (double)month < term; month++) {
    long double left_to_pay = credit_sum - (month_payment_diff * month);
    long double monthly_percent_payment = left_to_pay * month_tax_rate_dec;
    total_payment += month_payment_diff + monthly_percent_payment;
  }
  return total_payment;
}

long double overpayment(long double credit_sum, long double total_payment) {
  return total_payment - credit_sum;
}

double year_to_month(double year_term) { return year_term * 12; }
