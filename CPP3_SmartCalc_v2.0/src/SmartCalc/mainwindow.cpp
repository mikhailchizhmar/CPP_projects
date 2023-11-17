#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(Controller* c, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller(c) {
  ui->setupUi(this);

  graphwindow = new GraphWindow();
  graphwindow->setWindowTitle("Plot");

  ui->doubleSpinBox_X->setMaximum(100000000);
  ui->doubleSpinBox_X->setMinimum(-100000000);
  ui->doubleSpinBox_Xmax->setMaximum(10000000);
  ui->doubleSpinBox_Xmax->setMinimum(-10000000);
  ui->doubleSpinBox_Ymax->setMaximum(10000000);
  ui->doubleSpinBox_Ymax->setMinimum(-10000000);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(button_pressed()));

  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_open_bracket, SIGNAL(clicked()), this,
          SLOT(button_pressed()));
  connect(ui->pushButton_close_bracket, SIGNAL(clicked()), this,
          SLOT(button_pressed()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(button_pressed()));
  connect(ui->pushButton_power, SIGNAL(clicked()), this,
          SLOT(button_pressed()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(button_pressed()));

  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(button_pressed()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::button_pressed() {
  QPushButton* button = qobject_cast<QPushButton*>(sender());
  ui->label_answer->setText("");
  ui->lineEdit_input->setText(ui->lineEdit_input->text() + button->text());
}

void MainWindow::on_pushButton_C_clicked() {
  ui->label_answer->setText("");
  ui->lineEdit_input->setText("");
}

void MainWindow::on_pushButton_delete_clicked() {
  ui->lineEdit_input->backspace();
}

void MainWindow::on_pushButton_equal_clicked() {
  try {
    controller->validation(ui->lineEdit_input->text().toStdString());

    try {
      double result = controller->calculate(ui->doubleSpinBox_X->value());
      ui->label_answer->setText(QString::number(result, 'g', 15));
    } catch (const std::length_error& e) {
      ui->label_answer->setText("-Infinity");
    } catch (const std::logic_error& e) {
      ui->label_answer->setText("Error");
    } catch (const std::range_error& e) {
      ui->label_answer->setText("Infinity");
    }
  } catch (const std::length_error& e) {
    ui->label_answer->setText("String is too long");
  } catch (const std::logic_error& e) {
    ui->label_answer->setText("Invalid input");
  }
}

void MainWindow::on_pushButton_plot_clicked() {
  try {
    controller->validation(ui->lineEdit_input->text().toStdString());
    double step = 0.01, x0, Xmax = ui->doubleSpinBox_Xmax->value();

    QVector<double> x, y;
    x.clear();
    y.clear();

    for (x0 = -Xmax; x0 <= Xmax; x0 += step) {
      try {
        if (!std::isnan(controller->calculate(x0))) {
          x.push_back(x0);
          y.push_back(controller->calculate(x0));
        }

        if (x0 > -Xmax) {
          if (fabs(controller->calculate(x0) -
                   controller->calculate(x0 - step)) > 100) {
            y.pop_back();
            y.push_back(qQNaN());
          }
        }
      } catch (...) {
        continue;
      }
    }
    graphwindow->plot(x, y, ui->doubleSpinBox_Ymax->value(),
                      ui->doubleSpinBox_Xmax->value());
    graphwindow->show();
  } catch (const std::length_error& e) {
    ui->label_answer->setText("String is too long");
  } catch (const std::logic_error& e) {
    ui->label_answer->setText("Invalid input");
  }
}
