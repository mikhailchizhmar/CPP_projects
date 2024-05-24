/**
 * @file s21_calc_private_tests.cc
 * @author Team (TL: nidorina@student.21-school.ru)
 * nidorina@student.21-school.ru
 * newtonbe@student.21-school.ru
 * wellpetr@student.21-school.ru
 * @brief tests private methods of calculator class
 * @version 0.1
 * @date 2023-10-18
 * @copyright Copyright (c) 2023
 */
#include <gtest/gtest.h>
#define private public
#define protected public

#include "./s21_3dviewer_v2_tests.h"

namespace S21Test {

using namespace s21;

// arrange fixture i don't have enough time
class PrivateTest : public ::testing::Test {
 protected:
  void SetUp() {}
  void TearDown() {}
  // Model m;
};

/*----------------------------------validate expression-------------------*/

TEST_F(PrivateTest, private_methods_test) {
  // Arrange
  // Act
  // m.sum_(20, 1);
  // EXPECT_TRUE(m.res_ == 21);  // Assert
}
}  // namespace S21Test