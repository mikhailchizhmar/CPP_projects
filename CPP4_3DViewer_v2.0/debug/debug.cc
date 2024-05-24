/**
 * @file debug.cc
 * @author nidorina@student.21-school.ru
 * @brief for debugging the project
 * @version 0.2
 * @date 2023-11-23
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "./debug.h"

namespace Debug {}
using namespace s21;
using namespace Debug;
int main() {
  std::cout << std::setprecision(2) << std::fixed;
  Model m;
  // Controller c{m};
  // std::cout << c.getData(15, 6) << std::endl;
  // ShowExp(str);
  // showPolishStack(test);
  // showPolishVector(test);
}

namespace Debug {

void PrintMx(int& mx) {
  printf("\nmatrix %d x %d =\n", mx, mx);
  for (int i = 0; i < mx; ++i) {
    for (int j = 0; j < mx; j++) printf("%.8lf\t", .01);
    printf("\n");
  }
}

/** дорогой способ*/
template <typename T>
void swap_copy(T& x, T& y) {
  T tmp = x;  // copy ctor
  x = y;      // assign
  y = tmp;    // assing
}
/**более дешевый способ*/
template <typename T>
void swap_move(T& x, T& y) {
  T tmp = std::move(x);  // move ctor
  x = std::move(y);      // move assign
  y = std::move(tmp);    // move assign
}

// void showPolishStack(std::stack& stack) {
// std::cout << std::endl;
// ShowExp(stack.res_.size());
// for (; !stack.res_.empty(); stack.res_.pop()) {  // Act
// if (stack.res_.top().type == kNum) {
// ShowExp(stack.res_.top().value);
// } else {
// ShowExp(lexstr[stack.res_.top().type]);
// }
// }
// std::cout << std::endl;
// }
// void showPolishVector(std::vector& vect) {
// std::cout << std::endl;
// ShowExp(vect.ev_.size());
// for (auto& item : vect.ev_) {  // Act
// if (item.type == kNum) {
// ShowExp(item.value);
// } else {
// ShowExp(lexstr[item.type]);
// }
// }
// std::cout << std::endl;
// }
}  // namespace Debug

/** for classes that woriking with memory, file, net, multipotok*/
/* if realize one of them
you need to realize all
1. copy ctor
2. copy eq
3. move ctor
4. move eq
5. dtor
*/
