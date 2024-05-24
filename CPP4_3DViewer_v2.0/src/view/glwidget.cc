/**
 * @file glwidget.cc
 * @author Team (TL: nidorina@student.21-school.ru)
 * nidorina@student.21-school.ru
 * newtonbe@student.21-school.ru
 * wellpetr@student.21-school.ru
 * @brief realization of glwidget class
 * @version 0.1
 * @date 2023-12-21
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "./glwidget.h"

namespace s21 {
GLWidget::GLWidget(s21::Controller &ctrl, QWidget *parent)
    : ctrl_(ctrl), QOpenGLWidget(parent) {}

GLWidget::~GLWidget() {}

void GLWidget::initializeGL() { glEnable(GL_DEPTH_TEST); }

void GLWidget::resizeGL(int w, int h) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, w, h);
}

void GLWidget::paintGL() {
  setlocale(LC_NUMERIC, "C");
  glClearColor(ViewerColor.redF(), ViewerColor.greenF(), ViewerColor.blueF(),
               ViewerColor.alphaF());
  glPointSize(VertexSize);
  glLineWidth(LineWidth);
  if (ctrl_.getVtx() != nullptr) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    projectionStyleHandler();

    glTranslatef(0, 0, -2);

    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);

    drawObj();
  }
}

void GLWidget::drawObj() {
  glEnableClientState(GL_VERTEX_ARRAY);
  vertexStyleHandler();
  lineStyleHandler();
  glDisableClientState(GL_VERTEX_ARRAY);
}

void GLWidget::readObjFile(QString fileName) {
  QByteArray inputBytes = fileName.toUtf8();
  char *convertedFileName = strdup(inputBytes.constData());
  ctrl_.loadFromFile(convertedFileName);
  totalVertex = ctrl_.GetVtxCount();
  totalPolygons = ctrl_.GetFctCount();
  ctrl_.initialRescaleObj(scaleFactor);
  free(convertedFileName);
  update();
}

// void GLWidget::reshapePolygonIndices() {
//   if (polygonIndices != nullptr) {
//     free(polygonIndices);
//     polygonIndices = nullptr;
//   }
//   unsigned int polygonAmount = ctrl_.GetFctCount();
//   totalIndices =
//       ctrl_.GetTotalIndices() * 2 /*depends on the shape of a single
//       polygon*/;

//   polygonIndices = (unsigned int *)calloc(totalIndices, sizeof(unsigned
//   int));

//   for (size_t i = 0, k = 0; i < polygonAmount; i++) {
//     for (size_t j = 0, l = 0; j < ctrl_.GetFctVtx(i); j++, l += 2) {
//       polygonIndices[(k + l)] = ctrl_.GetPolygons()[i][j] - 1;
//       if (j + 1 == ctrl_.GetFctVtx(i)) {
//         polygonIndices[(k + l) + 1] = ctrl_.GetPolygons()[i][0] - 1;
//       } else {
//         polygonIndices[(k + l) + 1] = ctrl_.GetPolygons()[i][j + 1] - 1;
//       }
//     }
//     k += ctrl_.GetFctVtx(i) * 2;
//   }
// }
}  // namespace s21
