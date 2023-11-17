#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMainWindow>

namespace Ui {
class GraphWindow;
}

class GraphWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit GraphWindow(QWidget *parent = nullptr);
  void plot(QVector<double> x, QVector<double> y, double Ymax, double Xmax);
  ~GraphWindow();

 private:
  Ui::GraphWindow *ui;
};

#endif  // GRAPHWINDOW_H
