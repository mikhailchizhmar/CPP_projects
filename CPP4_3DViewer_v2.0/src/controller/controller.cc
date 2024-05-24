/**
 * @file controller.cc
 * @author Team (TL: nidorina@student.21-school.ru)
 * nidorina@student.21-school.ru
 * newtonbe@student.21-school.ru
 * wellpetr@student.21-school.ru
 * @brief realize controller class
 * @version 0.1
 * @date 2023-11-26
 * @copyright Copyright (c) 2023
 */

#include "./controller.h"

namespace s21 {

Controller::Controller(Facade& m) : model_(m) {}
// Controller::Controller(Model& m) : model_(m) {}

void Controller::loadFromFile(const char* fname) {
  model_.loadFromFile(fname);
  // model_.centerObj();
}

const double* Controller::getVtx() const noexcept {
  return model_.getVtx();
  // return model_.getVertexes();
}

std::vector<std::vector<unsigned int>>& Controller::GetPolygons() {
  return model_.GetPolygons();
};

unsigned int Controller::GetVtxCount() { return model_.GetVtxCount(); };

unsigned int Controller::GetFctCount() { return model_.GetFctCount(); };

unsigned int Controller::GetFctVtx(unsigned int i) {
  return model_.GetFctVtx(i);
};

unsigned int Controller::GetTotalIndices() { return model_.GetTotalIndices(); };

void Controller::rescaleObj(double scale) { model_.rescaleObj(scale); };

void Controller::moveX(double v) { model_.moveX(v); };

void Controller::moveY(double v) { model_.moveY(v); };

void Controller::moveZ(double v) { model_.moveZ(v); };

void Controller::rotateX(double v) { model_.rotateX(v); };

void Controller::rotateY(double v) { model_.rotateY(v); };

void Controller::rotateZ(double v) { model_.rotateZ(v); };

void Controller::initialRescaleObj(double scale) {
  model_.initialRescaleObj(scale);
};

}  // namespace s21
