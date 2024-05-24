/**
 * @file debug.h
 * @author nidorina@student.21-school.ru
 * @brief debug header
 * @version 0.2
 * @date 2023-11-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <cmath>
#include <exception>
#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>

#include "../src/controller/controller.h"
#include "../src/s21_3dviewer_v2.h"

namespace Debug {
#define ShowExp(Exp) std::cout << "{" #Exp "} is " << (Exp) << std::endl;

using namespace s21;
const char* lexstr[] = {
    "kErr",  /*!< error code */
    "kNum",  /*!< real number*/
    "kX",    /*!< variable of real number*/
    "kL_Br", /*!< left bracket*/
    "kR_Br", /*!< rigth bracket*/
    "kUp",   /*!< unary plus*/
    "kUm",   /*!< unary minus*/
    "kSum",  /*!< addition operation*/
    "kSub",  /*!< subtraction operation*/
    "kDiv",  /*!< division operation*/
    "kMul",  /*!< multiplication operation*/
    "kMod",  /*!< modulo division operation*/
    "kPow",  /*!< exponentiation operation*/
    "kCos",  /*!< finding the cosine*/
    "kSin",  /*!< finding the sine*/
    "kTan",  /*!< finding the tangent*/
    "kACos", /*!< finding the arccosine*/
    "kASin", /*!< finding the arcsine*/
    "kATan", /*!< finding the arctangent*/
    "kSqrt", /*!< root extraction*/
    "kLn",   /*!< finding the natural logarithm*/
    "kLog",  /*!< finding the  logarithm*/
};

void PrintMx(int& mx);
template <typename T>
void swap_copy(T& x, T& y);
template <typename T>
void swap_move(T& x, T& y);
// void showPolishStack(std::stack&);
// void showPolishVector(std::vector&);
}  // namespace Debug
#endif  // _DEBUG_H_