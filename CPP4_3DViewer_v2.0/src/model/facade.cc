/**
 * @file facade.cc
 * @author nidorina (nidorina@student.21-school.ru)
 * @brief realize facade class
 * @version 0.1
 * @date 2023-12-22
 * @copyright Copyright (c) 2023
 */
#include "./facade.h"
namespace s21 {

void Facade::loadFromFile(const char* fname) {
  model_.loadFromFile(fname);
  model_.centerObj();
}

const double* Facade::getVtx() const noexcept { return model_.getVertexes(); }

std::vector<std::vector<unsigned int>>& Facade::GetPolygons() {
  return model_.GetPolygons();
};

unsigned int Facade::GetVtxCount() { return model_.GetVtxCount(); };

unsigned int Facade::GetFctCount() { return model_.GetFctCount(); };

unsigned int Facade::GetFctVtx(unsigned int i) { return model_.GetFctVtx(i); };

unsigned int Facade::GetTotalIndices() { return model_.GetTotalIndices(); };

void Facade::initialRescaleObj(double scale) {
  model_.initialRescaleObj(scale);
};

void Facade::rescaleObj(double val) {
  model_.setAffine(new Rescale).doAffine(val);
};

void Facade::moveX(double val) { model_.setAffine(new MoveX).doAffine(val); };

void Facade::moveY(double val) { model_.setAffine(new MoveY).doAffine(val); };

void Facade::moveZ(double val) { model_.setAffine(new MoveZ).doAffine(val); };

void Facade::rotateX(double val) {
  model_.setAffine(new RotateX).doAffine(val);
};

void Facade::rotateY(double val) {
  model_.setAffine(new RotateY).doAffine(val);
};

void Facade::rotateZ(double val) {
  model_.setAffine(new RotateZ).doAffine(val);
};
}  // namespace s21