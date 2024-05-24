/**
 * @file model.cc
 * @author Team (TL: nidorina@student.21-school.ru)
 * nidorina@student.21-school.ru
 * newtonbe@student.21-school.ru
 * wellpetr@student.21-school.ru
 * @brief model class header
 * @version 0.1
 * @date 2023-11-26
 * @copyright Copyright (c) 2023
 */
#include "./model.h"

#include <math.h>

namespace s21 {

double Model::findMaxAxisDistance_() {
  double result = 0.0;
  double xDistance = bounds.x_max - bounds.x_min;
  double yDistance = bounds.y_max - bounds.y_min;
  double zDistance = bounds.z_max - bounds.z_min;
  if (xDistance > yDistance)
    result = (xDistance > zDistance) ? xDistance : zDistance;
  else
    result = (yDistance > zDistance) ? yDistance : zDistance;
  return result;
}

void Model::initialRescaleObj(double scaleVal) {
  double scaleApply = (scaleVal - (scaleVal * (-1))) / findMaxAxisDistance_();
  setAffine(new Rescale).doAffine(scaleApply);
}

Model& Model::setAffine(IStrategy* strategy) {
  strategy_ = std::move(strategy);
  return *this;
}

void Model::doAffine(double value) { strategy_->doAffine(this, value); }

}  // namespace s21
