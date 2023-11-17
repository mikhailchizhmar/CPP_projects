#include "graphwindow.h"

#include "ui_graphwindow.h"

GraphWindow::GraphWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::GraphWindow) {
  ui->setupUi(this);
}

GraphWindow::~GraphWindow() { delete ui; }

void GraphWindow::plot(QVector<double> x, QVector<double> y, double Ymax,
                       double Xmax) {
  ui->widget->clearGraphs();
  ui->widget->xAxis->setRange(-Xmax, Xmax);
  ui->widget->yAxis->setRange(-Ymax, Ymax);
  ui->widget->addGraph();
  ui->widget->graph(0)->data().clear();
  ui->widget->graph(0)->setLineStyle(QCPGraph::lsLine);
  ui->widget->graph(0)->addData(x, y);
  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
  ui->widget->replot();
}
