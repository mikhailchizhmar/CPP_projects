#ifndef SRC_SMARTCALCULATOR_H_
#define SRC_SMARTCALCULATOR_H_

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stack>
#include <string>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1

namespace s21 {

enum returns {
  NUMBER,
  X,
  PLUS,
  MINUS,
  MULTIPLICATION,
  DIVISION,
  MOD,
  POWER,
  COS,
  SIN,
  TAN,
  ACOS,
  ASIN,
  ATAN,
  SQRT,
  LN,
  LOG,
  OPENING_BRACKET,
  CLOSING_BRACKET
};

typedef struct {
  double value;
  int priority;
  int type;
} StackNode;

class SmartCalculator {
 public:
  SmartCalculator() = default;
  SmartCalculator(std::string input_, double x_value_)
      : input(input_), x_value(x_value_) {}
  ~SmartCalculator() = default;

  void setInput(std::string str) {
    input = str;
    result = 0;
  }
  std::string getInput() { return input; }
  void setX(double new_x) { x_value = new_x; }
  double getX() { return x_value; }
  double getResult() { return result; }

  /* Validation part */

  int is_sign(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' ? TRUE
                                                                     : FALSE);
  }

  int is_start_of_function(char c) {
    return (c == 'c' || c == 's' || c == 't' || c == 'a' || c == 'l' ? TRUE
                                                                     : FALSE);
  }

  int is_mod_before(int i) {
    return (i > 3 && input[i - 1] == 'd' && input[i - 2] == 'o' &&
                    input[i - 3] == 'm'
                ? TRUE
                : FALSE);
  }

  int is_cos(int i) {
    return (i < (int)input.length() - 5 && input[i + 1] == 'o' &&
                    input[i + 2] == 's' && input[i + 3] == '('
                ? TRUE
                : FALSE);
  }

  int is_sin(int i) {
    return (i < (int)input.length() - 5 && input[i + 1] == 'i' &&
                    input[i + 2] == 'n' && input[i + 3] == '('
                ? TRUE
                : FALSE);
  }

  int is_tan(int i) {
    return (i < (int)input.length() - 5 && input[i + 1] == 'a' &&
                    input[i + 2] == 'n' && input[i + 3] == '('
                ? TRUE
                : FALSE);
  }

  int is_exp(int i) {
    return (i < (int)input.length() - 1 && i > 0 &&
                    std::isdigit(input[i - 1]) && input[i] == 'e' &&
                    (std::isdigit(input[i + 1]) ||
                     (i < (int)input.length() - 2 && input[i + 1] == '-' &&
                      std::isdigit(input[i + 2])))
                ? TRUE
                : FALSE);
  }

  int is_function(int i);
  int only_one_dot();
  int delete_space();
  int check_brackets();
  void check_dot(int i, int *output);
  void check_sign(int i, int *output);
  void check_mod(int i, int *output);
  void check_x(int i, int *output);
  void check_number(int i, int *output);
  int check_exp(int i, int *output);
  int validation();

  /* Parser & RPN part */

  double parser_for_number(int *i);
  void parser_for_sign(char c, int *priority, int *type);
  void parser_for_functions(int *i, int *type);
  void parser();
  void infix_to_rpn();

  /* Calculation part */

  void one_number_check(int *flag);
  void fill_support(std::stack<StackNode> *Support);
  void fill_rpn(std::stack<StackNode> *Support);
  void operands_for_signs(std::stack<StackNode> *Support, double *left,
                          double *right);
  void operand_for_functions(std::stack<StackNode> *Support, double *operand);
  void calc_for_signs(double left, double right);
  void calc_for_functions(double operand);
  double calculate();

 private:
  std::string input;
  double x_value = 0.0;
  double result = 0.0;
  std::stack<StackNode> Infix;
  std::stack<StackNode> RPN;
};
}  // namespace s21

#endif  // SRC_SMARTCALCULATOR_H_