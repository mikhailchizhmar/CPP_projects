/**
 * @file style.cc
 * @author Team (TL: nidorina@student.21-school.ru)
 * nidorina@student.21-school.ru
 * newtonbe@student.21-school.ru
 * wellpetr@student.21-school.ru
 * @brief realize method of set style of openGL
 * @brief
 * @version 0.1
 * @date 2023-12-21
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "glwidget.h"
using namespace s21;
void GLWidget::widgetColorChange(QColor value) {
  ViewerColor = value;
  update();
}

void GLWidget::lineColorChange(QColor value) {
  LineColor = value;
  update();
}

void GLWidget::vertexColorChange(QColor value) {
  VertexColor = value;
  update();
}

void GLWidget::vertexTypeChange(int value) {
  VertexType = value;
  update();
}

void GLWidget::lineTypeChange(bool value) {
  LineSolid = value;
  update();
}

void GLWidget::projectionChange(bool value) {
  CentralProjection = value;
  update();
}

void GLWidget::lineWidthChange(double value) {
  LineWidth = value;
  update();
}

void GLWidget::vertexSizeChange(double value) {
  VertexSize = value;
  update();
}

void GLWidget::vertexStyleHandler() {
  glVertexPointer(3, GL_DOUBLE, 0, ctrl_.getVtx());
  switch (VertexType) {
    case 1:
      glColor3f(VertexColor.redF(), VertexColor.greenF(), VertexColor.blueF());
      glEnable(GL_POINT_SMOOTH);
      glDrawArrays(GL_POINTS, 0, ctrl_.GetVtxCount());
      break;
    case 2:
      glColor3f(VertexColor.redF(), VertexColor.greenF(), VertexColor.blueF());
      glDisable(GL_POINT_SMOOTH);
      glDrawArrays(GL_POINTS, 0, ctrl_.GetVtxCount());
      break;
    default:
      break;
  }
}

void GLWidget::projectionStyleHandler() {
  if (CentralProjection == true) {
    glFrustum(-1, 1, -1.0, 1.0, 1.0, 5000.0);
  } else {
    glOrtho(-1, 1, -1.0, 1.0, 1.0, 5000.0);
  }
}

void GLWidget::lineStyleHandler() {
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  if (!LineSolid) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00ff);
  }
  glColor3f(LineColor.redF(), LineColor.greenF(), LineColor.blueF());
  for (auto poly : ctrl_.GetPolygons())
    glDrawElements(GL_POLYGON, poly.size(), GL_UNSIGNED_INT, poly.data());
  if (!LineSolid) {
    glDisable(GL_LINE_STIPPLE);
  }
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
// for (int i{}; i != ctrl_.GetFctCount(); ++i) {
// unsigned int length = ctrl_.GetPolygons()[i].size();
// std::vector<unsigned> indices = ctrl_.GetPolygons()[i];
// indices.push_back(indices[0]);
// for (int j{}; j != indices.size(); ++j) {
//   indices[j] -= 1;
// }
// glDrawElements(GL_POLYGON, length, GL_UNSIGNED_INT, indices.data());
//}

// std::vector<int> test{}, test2{};
// test.push_back(indices[j]);
// glDrawArrays(GL_POLYGON, ctrl_.getVtx()[0], ctrl_.GetVtxCount());
// glDrawArrays(GL_QUADS, ctrl_.getVtx()[0], ctrl_.GetVtxCount());
// glDrawArrays(GL_LINES, ctrl_.getVtx()[0], ctrl_.GetVtxCount());
// glDrawArrays(GL_LINE_LOOP, ctrl_.getVtx()[0], ctrl_.GetVtxCount());
// glDrawArrays(GL_TRIANGLES, test[0], test.size());
// glDrawElements(GL_POLYGON, test.size(), GL_UNSIGNED_INT, test.data());
// glDrawElements(GL_LINE_LOOP, test.size(), GL_UNSIGNED_INT, test.data());
// std::cout << std::endl;

// std::cout << "total=" << test.size() << std::endl;
// std::cout << "polygonIndices=";
// for (int j{}; j != test.size(); ++j) std::cout << ", i=" << test[j];
// glDrawElements(GL_LINES, totalIndices, GL_UNSIGNED_INT, polygonIndices);
// std::cout << std::endl;

// std::vector<int> test{};
// for (int i{}; i != ctrl_.GetFctCount(); ++i)
//   for (int j{}; j != 4; ++j) {
//     test.push_back(ctrl_.GetPolygons()[i].vertexes[j]);
//     std::cout << ", i=" << ctrl_.GetPolygons()[i].vertexes[j];
//   }
// std::cout << std::endl;
// glColor3f(LineColor.redF(), LineColor.greenF(), LineColor.blueF());
// std::cout << "total: " << test.size() << std::endl;
// // glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, ctrl_.getVtx());
// glDrawElements(GL_LINES, test.size(), GL_UNSIGNED_INT, test.data());
