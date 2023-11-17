#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

#include "SmartCalculator.h"

namespace s21 {
class Controller {
 public:
  Controller() = default;
  Controller(SmartCalculator *calc) : model(calc) {}
  ~Controller() = default;

  double calculate(double x) {
    model->setX(x);
    return model->calculate();
  }

  int validation(std::string input) {
    model->setInput(input);
    return model->validation();
  }

 private:
  SmartCalculator *model;
};
}  // namespace s21

#endif  // SRC_CONTROLLER_H_