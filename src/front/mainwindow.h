#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QDoubleValidator>
#include <QMainWindow>
#include <QMessageBox>
#include <QVector>

extern "C" {
#include "../smart_calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  void x_input_display(bool val);
  bool is_x_set_check();
  QDoubleValidator loan_amount_validator;
  QDoubleValidator term_validator;
  QDoubleValidator interest_rate_validator;
  QDoubleValidator x_input_validator;
  QDoubleValidator range_validator;
  QDoubleValidator step_validator;
  QRegularExpressionValidator input_area_validator;
  int count;
  double tmp_x;
  bool is_set;

 private slots:
  void digit_nums();
  void bind_slots();
  void on_pushButton_mul_clicked();
  void on_pushButton_div_clicked();
  void on_pushButton_delete_symb_clicked();
  void on_pushButton_all_clear_clicked();
  void on_pushButton_equal_clicked();
  void plot_graph();
  void on_pushButton_plot_clicked();
  void on_pushButton_deposit_clicked();
  void on_pushButton_credit_clicked();
};
#endif  // MAINWINDOW_H
