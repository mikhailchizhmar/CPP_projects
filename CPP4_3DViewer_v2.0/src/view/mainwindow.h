/**
 * @file mainwindow.h
 * @author Team (TL: nidorina@student.21-school.ru)
 * nidorina@student.21-school.ru
 * newtonbe@student.21-school.ru
 * wellpetr@student.21-school.ru
 * @brief main window class header
 * @version 0.1
 * @date 2023-12-21
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef _SRC_VIEW_MAINWINDOW_H_
#define _SRC_VIEW_MAINWINDOW_H_

#include <QColorDialog>
#include <QFileDialog>
#include <QFileInfo>
#include <QImage>
#include <QMainWindow>
#include <QSettings>
#include <QTimer>

#include "../include/gif/gifimage/qgifimage.h"

// #include "../OpenGL/glwidget.h"
#include "../controller/controller.h"
#include "./glwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(s21::Controller &, QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  s21::GLWidget *glWidget;
  QSettings *settings;
  s21::Controller &ctrl_;
  QGifImage *gif;
  QTimer *timer;

  double currentMoveX = 0;
  double currentMoveY = 0;
  double currentMoveZ = 0;
  int currentRotateX = 0;
  int currentRotateY = 0;
  int currentRotateZ = 0;
  int currentScale = 100;

  void displayObjInfo(QString filePath);
  void adjustFont(QLabel *label);
  void initTransformSettings();
  void saveSettings();
  void downloadSettings();
  void colorChanger(QColor color, int value);
  void MakeGif();

 signals:
  void emitReadObjFile(QString fileName);
  void emitRotateObjX(int angle);
  void emitRotateObjY(int angle);
  void emitRotateObjZ(int angle);
  void emitZoomObj(int scale);
  void emitMoveObjX(double val);
  void emitMoveObjY(double val);
  void emitMoveObjZ(double val);
  void emitWidgetColorChange(QColor value);
  void emitLineColorChange(QColor value);
  void emitVertexColorChange(QColor value);
  void emitVertexTypeChange(int value);
  void emitLineTypeChange(bool value);
  void emitProjectionChange(bool value);
  void emitLineWidthChange(double value);
  void emitVertexSizeChange(double value);

 private slots:
  void on_pushButton_openFile_clicked();
  void on_horizontalSlider_rotX_valueChanged(int value);
  void on_spinBox_rotX_valueChanged(int value);
  void on_horizontalSlider_rotY_valueChanged(int value);
  void on_spinBox_rotY_valueChanged(int value);
  void on_horizontalSlider_rotZ_valueChanged(int value);
  void on_spinBox_rotZ_valueChanged(int value);

  void on_horizontalSlider_Scale_valueChanged(int value);

  void on_horizontalSlider_moveX_valueChanged(int value);
  void on_horizontalSlider_moveY_valueChanged(int value);
  void on_horizontalSlider_moveZ_valueChanged(int value);
  void on_spinBox_MoveX_valueChanged(int value);
  void on_spinBox_MoveY_valueChanged(int value);
  void on_spinBox_MoveZ_valueChanged(int value);

  void on_pushButton_widgetColor_clicked();
  void on_pushButton_lineColor_clicked();
  void on_pushButton_vertexColor_clicked();

  void on_radioButton_VertexNone_toggled(bool value);
  void on_radioButton_VertexCircle_toggled(bool value);
  void on_radioButton_VertexSquare_toggled(bool value);

  void on_radioButton_LineSolid_toggled(bool value);
  void on_radioButton_LineDashed_toggled(bool value);

  void on_radioButton_Central_toggled(bool value);
  void on_radioButton_Parallel_toggled(bool value);

  void on_horizontalSlider_LineSize_valueChanged(int value);
  void on_doubleSpinBox_LineSize_valueChanged(double value);

  void on_horizontalSlider_VertexSize_valueChanged(int value);
  void on_doubleSpinBox_VertexSize_valueChanged(double value);

  void on_pushButton_screenshot_clicked();
  /**
   * @brief record the gif
   */
  void on_pushButton_GIF_clicked();
  void take_screenshot();
  void save_gif();
};
#endif  // _SRC_VIEW_MAINWINDOW_H_
