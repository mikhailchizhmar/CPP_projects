#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <graphwindow.h>
#include <qmath.h>

#include "../Controller.h"

using namespace s21;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(Controller *c, QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  GraphWindow *graphwindow;
  Controller *controller;

 private slots:
  void button_pressed();
  void on_pushButton_C_clicked();
  void on_pushButton_delete_clicked();
  void on_pushButton_equal_clicked();
  void on_pushButton_plot_clicked();
};
#endif  // MAINWINDOW_H
