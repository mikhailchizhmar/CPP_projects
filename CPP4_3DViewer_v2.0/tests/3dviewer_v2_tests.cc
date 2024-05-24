/**
 * @file s21_3dviewer_tests.cpp
 * @author Team (TL: nidorina@student.21-school.ru)
 * nidorina@student.21-school.ru
 * newtonbe@student.21-school.ru
 * wellpetr@student.21-school.ru
 * @brief main gtest file
 * @version 0.1
 * @date 2023-06-30
 * @copyright Copyright (c) 2023
 */

#include <gtest/gtest.h>

#include "./s21_3dviewer_v2_tests.h"

GTEST_API_ int main(int argc, char **argv) {
  printf("Running main() from %s\n", __FILE__);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
