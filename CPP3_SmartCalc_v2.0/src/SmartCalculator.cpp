#include "SmartCalculator.h"

/* Validation part */

int s21::SmartCalculator::is_function(int i) {
  int shift = 0;
  if (input[i] == 'c') {
    if (is_cos(i)) shift = 2;
  } else if (input[i] == 's') {
    if (is_sin(i)) {
      shift = 2;
    } else if (i < (int)input.length() - 6 && input[i + 1] == 'q' &&
               input[i + 2] == 'r' && input[i + 3] == 't' &&
               input[i + 4] == '(')
      shift = 3;
  } else if (input[i] == 't') {
    if (is_tan(i)) shift = 2;
  } else if (input[i] == 'a') {
    if (is_cos(i + 1) || is_sin(i + 1) || is_tan(i + 1)) shift = 3;
  } else if (input[i] == 'l') {
    if (i < (int)input.length() - 4 && input[i + 1] == 'n' &&
        input[i + 2] == '(') {
      shift = 1;
    } else if (i < (int)input.length() - 5 && input[i + 1] == 'o' &&
               input[i + 2] == 'g' && input[i + 3] == '(')
      shift = 2;
  }
  /*помимо определения, является ли набор символов функцией, на выходе мы
   получаем число, на которое нужно сдвинуть i в валидации, чтобы не
   проверять другие символы*/
  return shift;
}

int s21::SmartCalculator::only_one_dot() {  // отсеить ввод по типу "125.5.7"
  int only_one_dot = TRUE;
  int count_dot = 0;
  for (int i = 0, j = 0; i < (int)input.length() && only_one_dot == TRUE; i++) {
    count_dot = 0;
    if (input[i] == '.' || std::isdigit(input[i])) {
      j = i;
      while (input[j] == '.' || std::isdigit(input[j])) {
        if (input[j] == '.') count_dot++;
        j++;
      }
      i = j;
    }
    if (count_dot > 1) only_one_dot = FALSE;
  }
  return only_one_dot;
}

int s21::SmartCalculator::delete_space() {
  int space_after_dot_or_char = FALSE;  // отсеить ввод по типу "123. 6"
  std::string copy = "";
  int shift = 0;
  for (int i = 0, j = 0; i < (int)input.length(); i++) {
    shift = 0;
    if (input[i] == '.') {
      if ((input[i + 1] == ' ') || (i != 0 && input[i - 1] == ' ')) {
        space_after_dot_or_char = TRUE;
        break;
      }
    }

    if (is_start_of_function(input[i])) {
      shift = is_function(i);
      if (!shift) {
        space_after_dot_or_char = TRUE;
        break;
      } else {
        for (int k = 0; k <= shift; k++) {
          copy.insert(copy.begin() + k + j, input[i + k]);
        }
      }
      i += shift;
      j += shift + 1;
    } else {
      if (input[i] != ' ') {
        copy.insert(copy.begin() + j, input[i]);
        j++;
      }
    }
  }
  input = copy;
  return space_after_dot_or_char;
}

int s21::SmartCalculator::check_brackets() {
  int count = 0;
  for (int i = 0; input[i] && count >= 0; i++) {
    if (input[i] == '(') {
      if (i != (int)input.length() - 1 && input[i + 1] == ')') {
        count = -1;
      } else
        count++;
    }
    if (input[i] == ')') count--;
  }
  return count;
  // проверка на скобки
}

void s21::SmartCalculator::check_dot(int i, int *output) {
  if (i == 0 || i == (int)input.length() - 1 || !std::isdigit(input[i + 1]) ||
      (i != 0 && !std::isdigit(input[i - 1]))) {
    *output = ERROR;
  }
  // если встретилась точка, после неё и перед ней должно быть число
}

void s21::SmartCalculator::check_sign(int i, int *output) {
  int condition_after_sign =
      (i == (int)input.length() - 1 ||
       (input[i + 1] != '(' && input[i + 1] != 'x' &&
        !std::isdigit(input[i + 1]) && !is_start_of_function(input[i + 1])));

  int condition_before_unary_sign =
      (i != 0 && input[i - 1] != '(' && input[i - 1] != ')' &&
       input[i - 1] != 'x' && !std::isdigit(input[i - 1]) &&
       input[i - 1] != 'e');

  int condition_before_sign =
      (i == 0 || (!std::isdigit(input[i - 1]) && input[i - 1] != ')' &&
                  input[i - 1] != 'x'));

  if (condition_after_sign) *output = ERROR;
  if (input[i] == '+' || input[i] == '-') {
    if (condition_before_unary_sign) *output = ERROR;
  } else {
    if (condition_before_sign) *output = ERROR;
  }
  // если встретился знак, после него должно идти число, скобка или функция
}

void s21::SmartCalculator::check_mod(int i, int *output) {
  int condition_before_mod =
      (i == 0 || (input[i - 1] != 'x' && !std::isdigit(input[i - 1]) &&
                  input[i - 1] != ')'));

  int condition_after_mod =
      (i > ((int)input.length() - 4) || input[i + 1] != 'o' ||
       input[i + 2] != 'd' ||
       (input[i + 3] != 'x' && !std::isdigit(input[i + 3]) &&
        input[i + 3] != '('));

  if (condition_before_mod || condition_after_mod) *output = ERROR;
  // после mod нет скобок, а только число, x или "(" (возможно функция или
  // "+-") перед mod может быть только x, число или ")" mod не может стоять в
  // начале или конце
}

void s21::SmartCalculator::check_x(int i, int *output) {
  int condition_before_x = (i > 0 && input[i - 1] != '(' &&
                            !is_sign(input[i - 1]) && !is_mod_before(i));

  int condition_after_x = (i < (int)input.length() - 1 && input[i + 1] != ')' &&
                           !is_sign(input[i + 1]) && input[i + 1] != 'm');

  if (condition_before_x || condition_after_x) *output = ERROR;
  // перед x может быть: ничего, "(", оператор или mod
  // после x можеть быть: ничего, ")", оператор или mod
}

void s21::SmartCalculator::check_number(int i, int *output) {
  int condition_before_number =
      (i > 0 && input[i - 1] != '(' && input[i - 1] != '.' &&
       !is_sign(input[i - 1]) && !std::isdigit(input[i - 1]) &&
       !is_mod_before(i) && input[i - 1] != 'e');

  int condition_after_number =
      (i < (int)input.length() - 1 && input[i + 1] != '.' &&
       input[i + 1] != ')' && !is_sign(input[i + 1]) &&
       !std::isdigit(input[i + 1]) && input[i + 1] != 'm' &&
       input[i + 1] != 'e');

  if (condition_before_number || condition_after_number) *output = ERROR;
}

int s21::SmartCalculator::check_exp(int i, int *output) {
  int shift = 0;
  int j = i + 1;
  if (input[j] == '-') {
    shift++;
    j++;
  }
  for (; j < (int)input.length() && !is_sign(input[j]) && input[j] != 'm' &&
         input[j] != ')';
       j++) {
    if (!std::isdigit(input[j]))
      *output = ERROR;
    else
      shift++;
  }
  return shift;
}

int s21::SmartCalculator::validation() {
  int output = OK;
  if (check_brackets() || delete_space() || !only_one_dot()) output = ERROR;
  for (int i = 0; i < (int)input.length() && output; i++) {
    if (is_exp(i)) {
      i += check_exp(i, &output);
    } else if (input[i] == '.') {
      check_dot(i, &output);
    } else if (is_sign(input[i])) {
      check_sign(i, &output);
    } else if (input[i] == 'm') {
      check_mod(i, &output);
      i += 2;
    } else if (input[i] == 'x') {
      check_x(i, &output);
    } else if (std::isdigit(input[i])) {
      check_number(i, &output);
    } else if (input[i] == '(' || input[i] == ')') {
      continue;
    } else if (is_start_of_function(input[i])) {
      i += is_function(i);
    } else
      output = ERROR;
  }

  if (output == ERROR) throw std::logic_error("Invalid string!");
  if ((int)input.length() > 255) throw std::length_error("Too long string!");
  return output;
}

/* Parser & RPN part */

double s21::SmartCalculator::parser_for_number(int *i) {
  std::string number_str;
  while (*i < (int)input.length() &&
         (std::isdigit(input[*i]) || input[*i] == '.')) {
    number_str += input[*i];
    (*i)++;
  }
  (*i)--;
  return std::atof(number_str.c_str());
}

void s21::SmartCalculator::parser_for_sign(char c, int *priority, int *type) {
  if (c == '+') {
    *type = PLUS;
    *priority = 1;
  } else if (c == '-') {
    *type = MINUS;
    *priority = 1;
  } else if (c == '*') {
    *type = MULTIPLICATION;
    *priority = 2;
  } else if (c == '/') {
    *type = DIVISION;
    *priority = 2;
  } else {
    *type = POWER;
    *priority = 3;
  }
}

void s21::SmartCalculator::parser_for_functions(int *i, int *type) {
  if (input[*i] == 'c') {
    if (is_cos(*i)) {
      (*i) += 2;
      *type = COS;
    }
  } else if (input[*i] == 's') {
    if (is_sin(*i)) {
      (*i) += 2;
      *type = SIN;
    } else if (*i < (int)input.length() - 6 && input[*i + 1] == 'q' &&
               input[*i + 2] == 'r' && input[*i + 3] == 't' &&
               input[*i + 4] == '(') {
      (*i) += 3;
      *type = SQRT;
    }
  } else if (input[*i] == 't') {
    if (is_tan(*i)) {
      (*i) += 2;
      *type = TAN;
    }
  } else if (input[*i] == 'a') {
    if (is_cos(*i + 1)) {
      *type = ACOS;
    } else if (is_sin(*i + 1)) {
      *type = ASIN;
    } else {
      *type = ATAN;
    }
    (*i) += 3;
  } else if (input[*i] == 'l') {
    if (*i < (int)input.length() - 4 && input[*i + 1] == 'n' &&
        input[*i + 2] == '(') {
      (*i) += 1;
      *type = LN;
    } else if (*i < (int)input.length() - 5 && input[*i + 1] == 'o' &&
               input[*i + 2] == 'g' && input[*i + 3] == '(') {
      (*i) += 2;
      *type = LOG;
    }
  }
}

void s21::SmartCalculator::parser() {
  std::stack<StackNode> Temp;
  int priority = 0;
  int type = 0;
  for (int i = 0; i < (int)input.length(); i++) {
    if (std::isdigit(input[i])) {
      Temp.push({parser_for_number(&i), 0, NUMBER});
    } else if (is_exp(i)) {
      Temp.push({0, 2, MULTIPLICATION});
      Temp.push({10, 0, NUMBER});
      Temp.push({0, 3, POWER});
      int is_minus = input[i + 1] == '-';
      if (is_minus) {
        Temp.push({0, 5, OPENING_BRACKET});
        Temp.push({0, 0, NUMBER});
        Temp.push({0, 1, MINUS});
        i++;
      }
      i++;
      Temp.push({parser_for_number(&i), 0, NUMBER});
      if (is_minus) Temp.push({0, 5, CLOSING_BRACKET});
    } else if (input[i] == 'x') {
      Temp.push({0, 0, X});
    } else if (is_sign(input[i])) {
      if ((input[i] == '+' || input[i] == '-') &&
          (i == 0 ||
           (i > 0 && !std::isdigit(input[i - 1]) && input[i - 1] != 'x' &&
            input[i - 1] != ')'))) {  // unary sign
        Temp.push({0, 0, NUMBER});
      }
      parser_for_sign(input[i], &priority, &type);
      Temp.push({0, priority, type});
    } else if (input[i] == '(') {
      Temp.push({0, 5, OPENING_BRACKET});
    } else if (input[i] == ')') {
      Temp.push({0, 5, CLOSING_BRACKET});
    } else if (input[i] == 'm') {
      Temp.push({0, 2, MOD});
      i += 2;
    } else {
      parser_for_functions(&i, &type);
      Temp.push({0, 4, type});
    }
  }

  while (!Temp.empty()) {
    Infix.push(Temp.top());
    Temp.pop();
  }
}

void s21::SmartCalculator::infix_to_rpn() {
  std::stack<StackNode> Ready;
  std::stack<StackNode> Support;

  while (!Infix.empty()) {
    if (Infix.top().type == NUMBER || Infix.top().type == X) {
      Ready.push({Infix.top().value, Infix.top().priority, Infix.top().type});
    } else if (Infix.top().type >= PLUS && Infix.top().type <= LOG) {
      while (!Support.empty() && Support.top().type >= PLUS &&
             Support.top().type <= LOG &&
             Support.top().priority >= Infix.top().priority) {
        Ready.push(
            {Support.top().value, Support.top().priority, Support.top().type});
        Support.pop();
      }
      Support.push({Infix.top().value, Infix.top().priority, Infix.top().type});
    } else if (Infix.top().type == OPENING_BRACKET) {
      Support.push({Infix.top().value, Infix.top().priority, Infix.top().type});
    } else if (Infix.top().type == CLOSING_BRACKET) {
      while (Support.top().type != OPENING_BRACKET) {
        Ready.push(
            {Support.top().value, Support.top().priority, Support.top().type});
        Support.pop();
      }
      Support.pop();
    }
    Infix.pop();
  }

  while (!Support.empty()) {
    Ready.push(
        {Support.top().value, Support.top().priority, Support.top().type});
    Support.pop();
  }

  while (!Ready.empty()) {
    RPN.push(Ready.top());
    Ready.pop();
  }
}

/* Calculation part */

void s21::SmartCalculator::one_number_check(int *flag) {
  if (RPN.size() == 1) {
    if (RPN.top().type == X) {
      result = x_value;
    } else {
      result = RPN.top().value;
    }
    *flag = 0;
  }  // если введено одно число или x, его и выводим
}

void s21::SmartCalculator::fill_support(std::stack<StackNode> *Support) {
  while (!RPN.empty() && RPN.top().type < PLUS) {
    Support->push({RPN.top().value, RPN.top().priority, RPN.top().type});
    RPN.pop();
  }  // Пока не встретили оператор, заполняем Support числами и x
}

void s21::SmartCalculator::fill_rpn(std::stack<StackNode> *Support) {
  while (!Support->empty()) {
    RPN.push(
        {Support->top().value, Support->top().priority, Support->top().type});
    Support->pop();
  }  // переносим числа и х обратно в RPN
}

void s21::SmartCalculator::operands_for_signs(std::stack<StackNode> *Support,
                                              double *left, double *right) {
  if (Support->top().type == X) {
    *right = x_value;
  } else {
    *right = Support->top().value;
  }
  Support->pop();

  if (Support->top().type == X) {
    *left = x_value;
  } else {
    *left = Support->top().value;
  }
  Support->pop();
}

void s21::SmartCalculator::operand_for_functions(std::stack<StackNode> *Support,
                                                 double *operand) {
  if (Support->top().type == X) {
    *operand = x_value;
  } else {
    *operand = Support->top().value;
  }
  Support->pop();
}

void s21::SmartCalculator::calc_for_signs(double left, double right) {
  if (RPN.top().type == PLUS) {
    RPN.pop();
    RPN.push({left + right, 0, NUMBER});
  } else if (RPN.top().type == MINUS) {
    RPN.pop();
    RPN.push({left - right, 0, NUMBER});
  } else if (RPN.top().type == MULTIPLICATION) {
    RPN.pop();
    RPN.push({left * right, 0, NUMBER});
  } else if (RPN.top().type == DIVISION) {
    RPN.pop();
    RPN.push({left / right, 0, NUMBER});
  } else if (RPN.top().type == MOD) {
    RPN.pop();
    RPN.push({fmod(left, right), 0, NUMBER});
  } else if (RPN.top().type == POWER) {
    RPN.pop();
    RPN.push({pow(left, right), 0, NUMBER});
  }
}

void s21::SmartCalculator::calc_for_functions(double operand) {
  if (RPN.top().type == COS) {
    RPN.pop();
    RPN.push({cos(operand), 0, NUMBER});
  } else if (RPN.top().type == SIN) {
    RPN.pop();
    RPN.push({sin(operand), 0, NUMBER});
  } else if (RPN.top().type == TAN) {
    RPN.pop();
    RPN.push({tan(operand), 0, NUMBER});
  } else if (RPN.top().type == ACOS) {
    RPN.pop();
    RPN.push({acos(operand), 0, NUMBER});
  } else if (RPN.top().type == ASIN) {
    RPN.pop();
    RPN.push({asin(operand), 0, NUMBER});
  } else if (RPN.top().type == ATAN) {
    RPN.pop();
    RPN.push({atan(operand), 0, NUMBER});
  } else if (RPN.top().type == SQRT) {
    RPN.pop();
    RPN.push({sqrt(operand), 0, NUMBER});
  } else if (RPN.top().type == LN) {
    RPN.pop();
    RPN.push({log(operand), 0, NUMBER});
  } else if (RPN.top().type == LOG) {
    RPN.pop();
    RPN.push({log10(operand), 0, NUMBER});
  }
}

double s21::SmartCalculator::calculate() {
  double left_operand = 0, right_operand = 0, operand = 0;
  std::stack<StackNode> Support;
  int flag = 1;

  parser();
  infix_to_rpn();
  one_number_check(&flag);

  while (!RPN.empty() && flag) {
    fill_support(&Support);

    if (RPN.top().type >= PLUS && RPN.top().type <= POWER) {
      operands_for_signs(&Support, &left_operand, &right_operand);
      calc_for_signs(left_operand, right_operand);
    } else {
      operand_for_functions(&Support, &operand);
      calc_for_functions(operand);
    }

    fill_rpn(&Support);
    one_number_check(&flag);
  }

  if (!RPN.empty()) {
    while (!RPN.empty()) {
      RPN.pop();
    }
  }
  if (std::isnan(result)) throw std::logic_error("ERROR");
  if (std::isinf(result) && result > 0) throw std::range_error("INFINITY");
  if (std::isinf(result) && result < 0) throw std::length_error("-INFINITY");
  return result;
}