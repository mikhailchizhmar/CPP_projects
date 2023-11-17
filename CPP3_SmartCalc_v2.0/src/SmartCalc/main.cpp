#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  SmartCalculator model;
  Controller controller(&model);
  MainWindow w(&controller);
  w.show();
  w.setWindowTitle("SmartCalc v2.0");
  return a.exec();
}
