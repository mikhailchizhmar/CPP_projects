/**
 * @file glwidget.h
 * @author Team (TL: nidorina@student.21-school.ru)
 * nidorina@student.21-school.ru
 * newtonbe@student.21-school.ru
 * wellpetr@student.21-school.ru
 * @brief glwidget class header
 * @version 0.1
 * @date 2023-12-21
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef _SRC_VIEW_GLWIDGET_H_
#define _SRC_VIEW_GLWIDGET_H_

#define GL_SILENCE_DEPRECATION

#include <QMessageBox>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QTimer>
#include <QWheelEvent>
#include <QWidget>
#include <QtOpenGL>

#include "../controller/controller.h"
#include "../s21_3dviewer_v2.h"

// #if defined(linux) || defined(_WIN32)
// #include <GL/glut.h>
// #else
// #include <GLUT/GLUT.h>
// #endif

namespace s21 {
class GLWidget : public QOpenGLWidget {
  Q_OBJECT

 public:
  unsigned int totalVertex = 0;
  unsigned int totalPolygons = 0;
  GLWidget(s21::Controller &, QWidget *parent = nullptr);
  ~GLWidget();

 public slots:
  void readObjFile(QString fileName);
  void rotateObjX(double angle);
  void rotateObjY(double angle);
  void rotateObjZ(double angle);

  void zoomObj(double scale);

  void moveObjX(double val);
  void moveObjY(double val);
  void moveObjZ(double val);

  void widgetColorChange(QColor value);
  void lineColorChange(QColor value);
  void vertexColorChange(QColor value);

  void vertexTypeChange(int value);
  void lineTypeChange(bool value);
  void projectionChange(bool value);

  void lineWidthChange(double value);
  void vertexSizeChange(double value);

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;

 private:
  s21::Controller ctrl_;

  /*----mouse manipulation----*/
  float xRot, yRot, mLastRotY, mLastRotX;
  double scaleFactor = 0.6f;
  QPointF mPos;

  /*----Colors----*/
  QColor VertexColor = QColor(242, 165, 60);
  QColor LineColor = QColor(242, 165, 60);
  QColor ViewerColor = QColor(58, 57, 57, 0);

  bool LineSolid = true;
  double LineWidth = 1.0;

  int VertexType = 0;
  double VertexSize = 1.0;

  bool CentralProjection = true;

  void drawObj();

  void vertexStyleHandler();
  void projectionStyleHandler();
  void lineStyleHandler();
};
}  // namespace s21
#endif  // _SRC_VIEW_GLWIDGET_H_
