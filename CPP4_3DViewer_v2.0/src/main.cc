/**
 * @file main.cc
 * @author Team (TL: nidorina@student.21-school.ru)
 * nidorina@student.21-school.ru
 * newtonbe@student.21-school.ru
 * wellpetr@student.21-school.ru
 * @brief application entry point
 * @version 0.1
 * @date 2023-12-21
 * @copyright Copyright (c) 2023
 */
#include <QApplication>

#include "./controller/controller.h"
#include "./view/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  using namespace s21;
  Facade fc;
  Controller ctrl{fc};
  MainWindow w{ctrl};
  w.show();
  return a.exec();
}
