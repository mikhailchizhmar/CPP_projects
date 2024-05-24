/**
 * @file transforamation.cc
 * @author Team (TL: nidorina@student.21-school.ru)
 * nidorina@student.21-school.ru
 * newtonbe@student.21-school.ru
 * wellpetr@student.21-school.ru
 * @brief realize methods to manipulate obj3d
 * @brief
 * @version 0.1
 * @date 2023-12-21
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "glwidget.h"
using namespace s21;
/*---------------------Mouse manipulation---------------------*/
void GLWidget::mousePressEvent(QMouseEvent *event) {
  mPos = event->position();
  mLastRotX = xRot;
  mLastRotY = yRot;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
  yRot = mLastRotY + event->position().x() - mPos.x();
  xRot = mLastRotX + event->position().y() - mPos.y();
  update();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event) {
  mLastRotX = xRot;
  mLastRotY = yRot;
  mPos = event->position();
}

void GLWidget::wheelEvent(QWheelEvent *event) {
  QPoint numPixels = event->pixelDelta();
  QPoint numDegrees = event->angleDelta() / 8;
  int numSteps = 0;
  if (!numPixels.isNull()) {
    numSteps = numPixels.y();
  } else if (!numDegrees.isNull()) {
    numSteps = numDegrees.y() / 15;
  }
  double zoomFactor = 1.0 + numSteps * 0.001f;
  if (zoomFactor < 0.1f) {
    zoomFactor = 0.1f;
  }
  ctrl_.rescaleObj(zoomFactor);
  update();
}

/*---------------------Rotation via buttons---------------------*/

void GLWidget::rotateObjX(double angle) {
  ctrl_.rotateX(angle / 57.29578);
  update();
}

void GLWidget::rotateObjY(double angle) {
  ctrl_.rotateY(angle / 57.29578);
  update();
}

void GLWidget::rotateObjZ(double angle) {
  ctrl_.rotateZ(angle / 57.29578);
  update();
}

/*---------------------Zoom via buttons---------------------*/
void GLWidget::zoomObj(double scale) {
  double zoomFactor = 1.0 + scale * 0.01f;
  if (zoomFactor < 0.1f) zoomFactor = 0.1f;
  ctrl_.rescaleObj(zoomFactor);
  update();
}

/*---------------------Move via buttons---------------------*/
void GLWidget::moveObjX(double val) {
  ctrl_.moveX(val);
  update();
}

void GLWidget::moveObjY(double val) {
  ctrl_.moveY(val);
  update();
}

void GLWidget::moveObjZ(double val) {
  ctrl_.moveZ(val);
  update();
}
