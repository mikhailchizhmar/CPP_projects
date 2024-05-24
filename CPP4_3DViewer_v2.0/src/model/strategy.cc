/**
 * @file strategy.cc
 * @author nidorina (nidorina@student.21-school.ru)
 * @brief realize strategy classes
 * @version 0.1
 * @date 2023-12-21
 * @copyright Copyright (c) 2023
 */

#include "./strategy.h"

#include <math.h>

namespace s21 {

void MoveX::doAffine(Obj3d* o, double value) {
  o->SetBounds().x_max += value;
  o->SetBounds().x_min += value;
  auto vtx = o->setVertexes();
  for (auto i{0LU}, end{vtx->size()}; i < end; i += 3) vtx->data()[i] += value;
}

void MoveY::doAffine(Obj3d* o, double v) {
  o->SetBounds().y_max += v;
  o->SetBounds().y_min += v;
  auto vtx = o->setVertexes();
  for (auto i{0LU}, end{vtx->size()}; i < end; i += 3) vtx->data()[i + 1] += v;
}

void MoveZ::doAffine(Obj3d* o, double v) {
  o->SetBounds().z_max += v;
  o->SetBounds().z_min += v;
  auto vtx = o->setVertexes();
  for (auto i{0LU}, end{vtx->size()}; i < end; i += 3) vtx->data()[i + 2] += v;
}

void RotateZ::doAffine(Obj3d* o, double v) {
  auto vtx = o->setVertexes();
  double s{sin(v)}, c{cos(v)};
  double temp_x_max = o->GetBounds().x_max;
  double temp_x_min = o->GetBounds().x_min;
  double temp_y_max = o->GetBounds().y_max;
  double temp_y_min = o->GetBounds().y_min;
  o->SetBounds().y_max = c * temp_x_max - s * temp_y_max;
  o->SetBounds().y_min = c * temp_x_min - s * temp_y_min;
  o->SetBounds().x_max = s * temp_x_max + c * temp_y_max;
  o->SetBounds().x_min = s * temp_x_min + c * temp_y_min;
  for (auto i{0LU}, end{vtx->size()}; i < end; i += 3) {
    double temp_x{vtx->data()[i + 0]}, temp_y{vtx->data()[i + 1]};
    vtx->data()[i + 0] = c * temp_x - s * temp_y;
    vtx->data()[i + 1] = s * temp_x + c * temp_y;
  }
}

void RotateX::doAffine(Obj3d* o, double v) {
  auto vtx = o->setVertexes();
  double s{sin(v)}, c{cos(v)};
  double temp_y_max = o->GetBounds().y_max;
  double temp_y_min = o->GetBounds().y_min;
  double temp_z_max = o->GetBounds().z_max;
  double temp_z_min = o->GetBounds().z_min;
  o->SetBounds().y_max = c * temp_y_max - s * temp_z_max;
  o->SetBounds().y_min = c * temp_y_min - s * temp_z_min;
  o->SetBounds().z_max = s * temp_y_max + c * temp_z_max;
  o->SetBounds().z_min = s * temp_y_min + c * temp_z_min;
  for (auto i{0LU}, end{vtx->size()}; i < end; i += 3) {
    double temp_y{vtx->data()[i + 1]}, temp_z{vtx->data()[i + 2]};
    vtx->data()[i + 1] = c * temp_y - s * temp_z;
    vtx->data()[i + 2] = s * temp_y + c * temp_z;
  }
}

void RotateY::doAffine(Obj3d* o, double v) {
  auto vtx = o->setVertexes();
  double s{sin(v)}, c{cos(v)};
  double temp_x_max = o->GetBounds().x_max;
  double temp_x_min = o->GetBounds().x_min;
  double temp_z_max = o->GetBounds().z_max;
  double temp_z_min = o->GetBounds().z_min;
  o->SetBounds().x_max = c * temp_x_max - s * temp_z_max;
  o->SetBounds().x_min = c * temp_x_min - s * temp_z_min;
  o->SetBounds().z_max = s * (-temp_x_max) + c * temp_z_max;
  o->SetBounds().z_min = s * (-temp_x_min) + c * temp_z_min;
  for (auto i{0LU}, end{vtx->size()}; i < end; i += 3) {
    double temp_x{vtx->data()[i + 0]}, temp_z{vtx->data()[i + 2]};
    vtx->data()[i + 0] = c * temp_x + s * temp_z;
    vtx->data()[i + 2] = s * (-temp_x) + c * temp_z;
  }
}

void Rescale::doAffine(Obj3d* o, double v) {
  auto vtx = o->setVertexes();
  o->SetBounds().x_max *= v;
  o->SetBounds().x_min *= v;
  o->SetBounds().y_max *= v;
  o->SetBounds().y_min *= v;
  o->SetBounds().z_max *= v;
  o->SetBounds().z_min *= v;
  for (auto end{vtx->size()}, i{0LU}; i < end; i++) vtx->data()[i] *= v;
}

};  // namespace s21