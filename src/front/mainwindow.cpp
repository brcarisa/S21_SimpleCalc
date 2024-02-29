#include "mainwindow.h"

#include <float.h>

#include <QDebug>
#include <QMessageBox>
#include <string>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      loan_amount_validator(0, 100000000, 7, this),
      term_validator(1, 60, 0, this),
      interest_rate_validator(0.1, 1000, 2, this),
      x_input_validator(-9999999999999999, 9999999999999999, 17, this),
      range_validator(-999999, 999999, 7, this),
      step_validator(0.1, 20, 1, this),
      input_area_validator(QRegularExpression(
          "^[( "
          "|sin|cos|ln|tan|log|mod|asin|atan|acos|sqrt|)0-9^/*-+xe.]{255}")) {
  ui->setupUi(this);
  bind_slots();
  is_set = false;
  QLocale locale(QLocale::English);
  // set_locales
  x_input_validator.setLocale(locale);
  loan_amount_validator.setLocale(locale);
  term_validator.setLocale(locale);
  interest_rate_validator.setLocale(locale);
  range_validator.setLocale(locale);
  step_validator.setLocale(locale);
  // set_notations
  x_input_validator.setNotation(QDoubleValidator::StandardNotation);
  loan_amount_validator.setNotation(QDoubleValidator::StandardNotation);
  term_validator.setNotation(QDoubleValidator::StandardNotation);
  interest_rate_validator.setNotation(QDoubleValidator::StandardNotation);
  range_validator.setNotation(QDoubleValidator::StandardNotation);
  step_validator.setNotation(QDoubleValidator::StandardNotation);
  // validators_for_range_plot
  ui->min_range_x->setValidator(&range_validator);
  ui->min_range_y->setValidator(&range_validator);
  ui->max_range_x->setValidator(&range_validator);
  ui->max_range_y->setValidator(&range_validator);
  ui->lineEdit_step->setValidator(&step_validator);
  // smart_calc_validators
  ui->lineEdit_x_input->setValidator(&x_input_validator);
  ui->show_result->setValidator(&input_area_validator);
  // loan_validators
  ui->total_loan_amount_text->setValidator(&loan_amount_validator);
  ui->term_text->setValidator(&term_validator);
  ui->interest_rate_text->setValidator(&interest_rate_validator);
  // dep_validators
  ui->deposit_amount->setValidator(&loan_amount_validator);
  ui->placement_period->setValidator(&term_validator);
  ui->tax_rate_text->setValidator(&interest_rate_validator);
  ui->monthly_additions->setValidator(&loan_amount_validator);
  ui->monthly_withdrawals->setValidator(&loan_amount_validator);
}

MainWindow::~MainWindow() { delete ui; }

//ConnectionsForButtons
void MainWindow::bind_slots() {
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digit_nums()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digit_nums()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digit_nums()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digit_nums()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digit_nums()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digit_nums()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digit_nums()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digit_nums()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digit_nums()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digit_nums()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(digit_nums()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(digit_nums()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(digit_nums()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(digit_nums()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(digit_nums()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(digit_nums()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(digit_nums()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digit_nums()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digit_nums()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(digit_nums()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digit_nums()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(digit_nums()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digit_nums()));
  connect(ui->pushButton_open_bracket, SIGNAL(clicked()), this,
          SLOT(digit_nums()));
  connect(ui->pushButton_close_bracket, SIGNAL(clicked()), this,
          SLOT(digit_nums()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(digit_nums()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digit_nums()));
}


//MethodForDrawGraph
void MainWindow::plot_graph() {
  if (ui->min_range_x->text().isEmpty() || ui->min_range_y->text().isEmpty() ||
      ui->max_range_x->text().isEmpty() || ui->max_range_y->text().isEmpty() ||
      ui->lineEdit_step->text().isEmpty()) {
    QMessageBox::warning(this, "not all filled",
                         "Please fill in all fields to enter");
  } else {
    std::string str = ui->show_result->text().toStdString();
    const char *cstr = str.c_str();
    ui->custom_plot->clearGraphs();
    QVector<double> x, y;
    long double minX = (long double)ui->min_range_x->text().toDouble();
    long double maxX = (long double)ui->max_range_x->text().toDouble();
    long double minY = (long double)ui->min_range_y->text().toDouble();
    long double maxY = (long double)ui->max_range_y->text().toDouble();
    long double step = (long double)ui->lineEdit_step->text().toDouble();
    count = (maxX - minX) / step + 2;
    if (count > 1000000) {
      count = 1000000;
    }
    tmp_x = minX;
    for (int i = 0; i < count; i++) {
      long double res = 0.0;
      calculate_str_api_with_x(cstr, (long double)tmp_x + i * step, &res);
      if (res >= minY && res <= maxY) {
        x.push_back(minX + i * step);
        y.push_back((double)res);
      }
    }
    ui->custom_plot->addGraph();
    ui->custom_plot->graph(0)->setData(x, y);
    ui->custom_plot->yAxis->setRange(-21, 21);
    ui->custom_plot->xAxis->setRange(-21, 21);
    ui->custom_plot->setInteraction(QCP::iRangeZoom, true);
    ui->custom_plot->setInteraction(QCP::iRangeDrag, true);
    ui->custom_plot->replot();
  }
}

void MainWindow::digit_nums() {
  QPushButton *pressed_btn = (QPushButton *)sender();
  QByteArray btn_text = pressed_btn->text().toLocal8Bit();
  const char *c_str = btn_text.data();

  if (ui->show_result->text() == "0" && !strpbrk(c_str, "+-/*.^")) {
    ui->show_result->setText("");
  }
  if (strpbrk(c_str, "0123456789x+-()^.m")) {
    ui->show_result->setText(ui->show_result->text() + pressed_btn->text());
  } else {
    ui->show_result->setText(ui->show_result->text() + pressed_btn->text() +
                             "(");
  }
}


//ExeceptionForOtherButtons
void MainWindow::on_pushButton_mul_clicked() {
  ui->show_result->setText(ui->show_result->text() + "*");
}

void MainWindow::on_pushButton_div_clicked() {
  ui->show_result->setText(ui->show_result->text() + "/");
}

void MainWindow::on_pushButton_delete_symb_clicked() {
  QString currentText = ui->show_result->text();
  currentText.chop(1);
  ui->show_result->setText(currentText);
  if (ui->show_result->text() == "") {
    ui->show_result->setText("0");
  }
}

void MainWindow::on_pushButton_all_clear_clicked() {
  ui->show_result->setText("0");
}

void MainWindow::x_input_display(bool val) {
  if (val) {
    ui->label_fx->setVisible(true);
    ui->lineEdit_x_input->setVisible(true);
  } else {
    ui->label_fx->setVisible(false);
    ui->lineEdit_x_input->setVisible(false);
  }
}

bool MainWindow::is_x_set_check() { return !ui->label_fx->text().isEmpty(); }

void MainWindow::on_pushButton_equal_clicked() {
  std::string str = ui->show_result->text().toStdString();
  const char *cstr = str.c_str();
  bool is_error = false;
  if (ui->pushButton_equal->text() == "=") {
    if (ui->label_fx->isVisible()) {
      if (is_x_set_check()) {
        long double res = 0;
        is_error = calculate_str_api_with_x(
            cstr, (long double)ui->lineEdit_x_input->text().toDouble(), &res);
        if (!is_error) {
          QString result = QString::number(res, 'g', 7);
          ui->show_result->setText(result);
        } else {
          ui->show_result->setText(("ERROR"));
        }
      } else {
        QMessageBox::warning(this, "x not defined",
                             "Please, enter value for x");
      }
    } else {
      long double res = 0;
      is_error = calculate_str_api(cstr, &res);
      if (!is_error) {
        QString result = QString::number(res, 'g', 7);
        ui->show_result->setText(result);
      } else {
        ui->show_result->setText("ERROR");
      }
    }
  }
}

void MainWindow::on_pushButton_plot_clicked() { plot_graph(); }

void MainWindow::on_pushButton_deposit_clicked() {
  if (ui->deposit_amount->text().isEmpty() ||
      ui->placement_period->text().isEmpty() ||
      ui->interest_rate_text_dep->text().isEmpty() ||
      (!ui->radio_month_dep->isChecked() &&
       !ui->radio_years_dep->isChecked()) ||
      (!ui->freq_payments_radio_month->isChecked() &&
       !ui->freq_payments_radio_year->isChecked())) {
    QMessageBox::warning(this, "not all field",
                         "Please fill in all fields to enter");
  } else {
    long double dep_amount = ui->deposit_amount->text().toDouble();
    long double term = ui->placement_period->text().toDouble();
    if (ui->radio_years_dep->isChecked()) {
      term = year_to_month(term);
    }
    long double interest_rate = ui->interest_rate_text_dep->text().toDouble();
    long double tax_rate = ui->tax_rate_text->text().toDouble();
    bool is_capitalisation = ui->check_capitalozation->isChecked();
    int mode = ui->freq_payments_radio_month->isChecked() ? MONTH : YEAR;
    long double month_additions = ui->monthly_additions->text().toDouble();
    long double month_withdrawals = ui->monthly_withdrawals->text().toDouble();
    long double total_earn =
        get_total_profit(&dep_amount, term, interest_rate, mode,
                         is_capitalisation, month_additions, month_withdrawals);
    long double sum_tax = get_tax_sum(total_earn, tax_rate);
    long double sum_with_tax = sum_after_tax(dep_amount, total_earn, sum_tax);
    QString te = QString::number(total_earn, 'g', 7);
    QString st = QString::number(sum_tax, 'g', 7);
    QString sat = QString::number(sum_with_tax, 'g', 7);
    ui->interest_charges->setText(te);
    ui->tax_amount->setText(st);
    ui->amount_deposit->setText(sat);
  }
}

void MainWindow::on_pushButton_credit_clicked() {
  if (ui->total_loan_amount_text->text().isEmpty() ||
      ui->total_loan_amount_text->text().isEmpty() ||
      ui->interest_rate_text->text().isEmpty() ||
      ((!ui->radio_years->isChecked() && !ui->radio_month->isChecked()) ||
       (!ui->annuity_radio_btn->isChecked() &&
        !ui->diff_radio_btn->isChecked()))) {
    QMessageBox::warning(this, "not all field",
                         "Please fill in all fields to enter");
  } else {
    long double loan_amount = ui->total_loan_amount_text->text().toDouble();
    double term = ui->term_text->text().toDouble();
    if (ui->radio_years->isChecked()) {
      term = year_to_month(term);
    }
    long double rate = ui->interest_rate_text->text().toDouble();
    if (ui->annuity_radio_btn->isChecked()) {
      long double monthly_payment =
          monthly_payment_annuity(loan_amount, term, rate);
      long double total_pay = total_payment_annuity(monthly_payment, term);
      long double overpay = overpayment(loan_amount, total_pay);
      QString mp = QString::number(monthly_payment, 'g', 7);
      QString tp = QString::number(total_pay, 'g', 7);
      QString ovr = QString::number(overpay, 'g', 7);
      ui->monthly_payment_text->setText(mp);
      ui->total_payout_text->setText(tp);
      ui->overpayment_on_loan_text->setText(ovr);
    } else {
      long double total_pay_dif = total_payment_diff(loan_amount, term, rate);
      long double monthly_payment_dif =
          monthly_payment_diff(total_pay_dif, term);
      long double overpay_dif = overpayment(loan_amount, total_pay_dif);
      QString mpd = QString::number(monthly_payment_dif, 'g', 7);
      QString tpd = QString::number(total_pay_dif, 'g', 7);
      QString ovrd = QString::number(overpay_dif, 'g', 7);
      ui->monthly_payment_text->setText(mpd + " average");
      ui->total_payout_text->setText(tpd);
      ui->overpayment_on_loan_text->setText(ovrd);
    }
  }
}
