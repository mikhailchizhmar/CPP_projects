#include <gtest/gtest.h>

#include "my_matrix_oop.h"
using namespace std;

TEST(constructor_test, constructor_default_1) {
  MyMatrix A;
  ASSERT_EQ(A.GetRows(), 3);
  ASSERT_EQ(A.GetCols(), 3);
}

TEST(constructor_test, constructor_parameters_1) {
  MyMatrix A(4, 5);
  ASSERT_EQ(A.GetRows(), 4);
  ASSERT_EQ(A.GetCols(), 5);
}

TEST(constructor_test, constructor_parameters_2) {
  MyMatrix A(400, 500);
  ASSERT_EQ(A.GetRows(), 400);
  ASSERT_EQ(A.GetCols(), 500);
}

TEST(constructor_test, constructor_parameters_3) {
  ASSERT_THROW(MyMatrix A(0, 5), invalid_argument);
}

TEST(constructor_test, constructor_parameters_4) {
  ASSERT_THROW(MyMatrix A(6, -5), invalid_argument);
}

TEST(constructor_test, constructor_copy_1) {
  MyMatrix A(2, 4);
  MyMatrix B(A);
  ASSERT_EQ(B.GetRows(), 2);
  ASSERT_EQ(B.GetCols(), 4);
}

TEST(constructor_test, constructor_move_1) {
  MyMatrix A(1, 5);
  MyMatrix B(move(A));
  ASSERT_EQ(B.GetRows(), 1);
  ASSERT_EQ(B.GetCols(), 5);
  ASSERT_EQ(A.GetRows(), 0);
  ASSERT_EQ(A.GetCols(), 0);
}

TEST(accessors_and_mutators_test, setter_1) {
  MyMatrix A(2, 6);
  // A.initialize(1);
  // A.print_matrix();
  A.SetRows(4);
  ASSERT_EQ(A.GetRows(), 4);
  ASSERT_EQ(A.GetCols(), 6);
  // A.print_matrix();
}

TEST(accessors_and_mutators_test, setter_2) {
  MyMatrix A(3, 5);
  A.SetRows(2);
  ASSERT_EQ(A.GetRows(), 2);
  ASSERT_EQ(A.GetCols(), 5);
}

TEST(accessors_and_mutators_test, setter_3) {
  MyMatrix A(3, 5);
  A.SetRows(3);
  ASSERT_EQ(A.GetRows(), 3);
  ASSERT_EQ(A.GetCols(), 5);
}

TEST(accessors_and_mutators_test, setter_4) {
  MyMatrix A(2, 6);
  A.SetCols(4);
  ASSERT_EQ(A.GetRows(), 2);
  ASSERT_EQ(A.GetCols(), 4);
}

TEST(accessors_and_mutators_test, setter_5) {
  MyMatrix A(2, 3);
  A.SetCols(7);
  ASSERT_EQ(A.GetRows(), 2);
  ASSERT_EQ(A.GetCols(), 7);
}

TEST(accessors_and_mutators_test, setter_6) {
  MyMatrix A(2, 3);
  A.SetCols(3);
  ASSERT_EQ(A.GetRows(), 2);
  ASSERT_EQ(A.GetCols(), 3);
}

TEST(accessors_and_mutators_test, setter_7) {
  MyMatrix A(2, 3);
  ASSERT_THROW(A.SetCols(-3), invalid_argument);
  ASSERT_EQ(A.GetRows(), 2);
  ASSERT_EQ(A.GetCols(), 3);
}

TEST(accessors_and_mutators_test, setter_8) {
  MyMatrix A(2, 3);
  ASSERT_THROW(A.SetRows(0), invalid_argument);
  ASSERT_EQ(A.GetRows(), 2);
  ASSERT_EQ(A.GetCols(), 3);
}

TEST(operations, eq_matrix_1) {
  MyMatrix A(2, 3);
  A.initialize(1.35657);
  MyMatrix B(A);
  ASSERT_TRUE(A.EqMatrix(B));
}

TEST(operations, eq_matrix_2) {
  MyMatrix A(2, 3);
  A.initialize(7);
  MyMatrix B(1, 3);
  B.initialize(7);
  ASSERT_FALSE(A.EqMatrix(B));
}

TEST(operations, eq_matrix_3) {
  MyMatrix A(2, 3);
  A.initialize(9);
  MyMatrix B(2, 7);
  B.initialize(9);
  ASSERT_FALSE(A.EqMatrix(B));
}

TEST(operations, eq_matrix_4) {
  MyMatrix A(2, 3);
  A.initialize(0.1234567);
  MyMatrix B(2, 3);
  B.initialize(0.1234567);
  ASSERT_TRUE(A.EqMatrix(B));
}

TEST(operations, eq_matrix_5) {
  MyMatrix A(2, 3);
  A.initialize(0.1234567);
  MyMatrix B(2, 3);
  B.initialize(0.1234568);
  ASSERT_FALSE(A.EqMatrix(B));
}

TEST(operations, eq_matrix_6) {
  MyMatrix A(2, 3);
  MyMatrix B(move(A));
  ASSERT_THROW(B.EqMatrix(A), logic_error);
}

TEST(operations, sum_matrix_1) {
  MyMatrix A(2, 3);
  MyMatrix B(move(A));
  ASSERT_THROW(B.SumMatrix(A), logic_error);
}

TEST(operations, sum_matrix_2) {
  MyMatrix A(2, 3);
  MyMatrix B(3, 3);
  ASSERT_THROW(B.SumMatrix(A), logic_error);
}

TEST(operations, sum_matrix_3) {
  MyMatrix A(2, 3);
  MyMatrix B(2, 4);
  ASSERT_THROW(B.SumMatrix(A), logic_error);
}

TEST(operations, sum_matrix_4) {
  MyMatrix A(2, 3);
  A.initialize(2);
  MyMatrix B(2, 3);
  B.initialize(3);
  A.SumMatrix(B);
  MyMatrix Expected(2, 3);
  Expected.initialize(5);

  ASSERT_TRUE(A.EqMatrix(Expected));
}

TEST(operations, sub_matrix_1) {
  MyMatrix A(2, 3);
  MyMatrix B(move(A));
  ASSERT_THROW(B.SubMatrix(A), logic_error);
}

TEST(operations, sub_matrix_2) {
  MyMatrix A(2, 3);
  MyMatrix B(3, 3);
  ASSERT_THROW(B.SubMatrix(A), logic_error);
}

TEST(operations, sub_matrix_3) {
  MyMatrix A(2, 3);
  MyMatrix B(2, 4);
  ASSERT_THROW(B.SubMatrix(A), logic_error);
}

TEST(operations, sub_matrix_4) {
  MyMatrix A(2, 3);
  A.initialize(7);
  MyMatrix B(2, 3);
  B.initialize(5);
  A.SubMatrix(B);
  MyMatrix Expected(2, 3);
  Expected.initialize(2);
  ASSERT_TRUE(A.EqMatrix(Expected));
}

TEST(operations, mul_number_1) {
  MyMatrix A(2, 3);
  MyMatrix B(move(A));
  ASSERT_THROW(A.MulNumber(4.5638), logic_error);
}

TEST(operations, mul_number_2) {
  MyMatrix A(5, 5);
  A.initialize(5);
  A.MulNumber(4);
  MyMatrix Expected(5, 5);
  Expected.initialize(20);
  ASSERT_TRUE(A.EqMatrix(Expected));
}

TEST(operations, mul_matrix_1) {
  MyMatrix A(2, 3);
  MyMatrix B(move(A));
  ASSERT_THROW(A.MulMatrix(B), logic_error);
}

TEST(operations, mul_matrix_2) {
  MyMatrix A(2, 4);
  MyMatrix B(2, 4);
  ASSERT_THROW(A.MulMatrix(B), logic_error);
}

TEST(operations, mul_matrix_3) {
  MyMatrix A(3, 3);
  A.initialize(1);
  MyMatrix B(3, 3);
  B.initialize(2);
  MyMatrix Expected(3, 3);
  Expected.initialize(6);
  A.MulMatrix(B);
  ASSERT_TRUE(A.EqMatrix(Expected));
}

TEST(operations, transpose_1) {
  MyMatrix A(2, 3);
  MyMatrix B(move(A));
  ASSERT_THROW(A.Transpose(), logic_error);
}

TEST(operations, transpose_2) {
  MyMatrix A(2, 3);
  MyMatrix B = A.Transpose();
  ASSERT_EQ(B.GetRows(), 3);
  ASSERT_EQ(B.GetCols(), 2);
}

TEST(operations, transpose_3) {
  MyMatrix A(3, 3);
  MyMatrix B = A.Transpose();
  ASSERT_EQ(B.GetRows(), 3);
  ASSERT_EQ(B.GetCols(), 3);
}

TEST(operations, transpose_4) {
  MyMatrix A(7, 1);
  MyMatrix B = A.Transpose();
  ASSERT_EQ(B.GetRows(), 1);
  ASSERT_EQ(B.GetCols(), 7);
}

TEST(operations, determinant_1) {
  MyMatrix A(3, 3);
  MyMatrix B(move(A));
  ASSERT_THROW(A.Determinant(), logic_error);
}
TEST(operations, determinant_2) {
  MyMatrix A(2, 3);
  ASSERT_THROW(A.Determinant(), logic_error);
}
TEST(operations, determinant_3) {
  MyMatrix A(3, 3);
  A(0, 0) = 21;
  A(0, 1) = 45;
  A(0, 2) = 6;
  A(1, 0) = 8;
  A(1, 1) = 2;
  A(1, 2) = 7;
  A(2, 0) = 4;
  A(2, 1) = 7;
  A(2, 2) = 6;
  ASSERT_EQ(A.Determinant(), -1389);
}

TEST(operations, determinant_4) {
  MyMatrix A(1, 1);
  A(0, 0) = 7;
  ASSERT_EQ(A.Determinant(), 7);
}

TEST(operations, determinant_5) {
  MyMatrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  ASSERT_EQ(A.Determinant(), -2);
}

TEST(operations, calc_complements_1) {
  MyMatrix A(3, 3);
  MyMatrix B(move(A));
  ASSERT_THROW(A.CalcComplements(), logic_error);
}

TEST(operations, calc_complements_2) {
  MyMatrix A(2, 3);
  ASSERT_THROW(A.CalcComplements(), logic_error);
}
TEST(operations, calc_complements_3) {
  MyMatrix A(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 0;
  A(1, 1) = 4;
  A(1, 2) = 2;
  A(2, 0) = 5;
  A(2, 1) = 2;
  A(2, 2) = 1;
  MyMatrix B = A.CalcComplements();
  MyMatrix Expected(3, 3);
  Expected(0, 0) = 0;
  Expected(0, 1) = 10;
  Expected(0, 2) = -20;
  Expected(1, 0) = 4;
  Expected(1, 1) = -14;
  Expected(1, 2) = 8;
  Expected(2, 0) = -8;
  Expected(2, 1) = -2;
  Expected(2, 2) = 4;
  for (int i = 0; i < B.GetRows(); i++) {
    for (int j = 0; j < B.GetCols(); j++) {
      ASSERT_EQ(B(i, j), Expected(i, j));
    }
  }
}

TEST(operations, inverse_matrix_1) {
  MyMatrix A(3, 3);
  MyMatrix B(move(A));
  ASSERT_THROW(A.InverseMatrix(), logic_error);
}

TEST(operations, inverse_matrix_2) {
  MyMatrix A(2, 2);
  A(0, 0) = 2;
  A(0, 1) = 2;
  A(1, 0) = 2;
  A(1, 1) = 2;
  ASSERT_THROW(A.InverseMatrix(), logic_error);
}

TEST(operations, inverse_matrix_3) {
  MyMatrix A(3, 3);
  A(0, 0) = 2;
  A(0, 1) = 5;
  A(0, 2) = 7;
  A(1, 0) = 6;
  A(1, 1) = 3;
  A(1, 2) = 4;
  A(2, 0) = 5;
  A(2, 1) = -2;
  A(2, 2) = -3;
  MyMatrix B = A.InverseMatrix();
  MyMatrix Expected(3, 3);
  Expected(0, 0) = 1;
  Expected(0, 1) = -1;
  Expected(0, 2) = 1;
  Expected(1, 0) = -38;
  Expected(1, 1) = 41;
  Expected(1, 2) = -34;
  Expected(2, 0) = 27;
  Expected(2, 1) = -29;
  Expected(2, 2) = 24;
  for (int i = 0; i < B.GetRows(); i++) {
    for (int j = 0; j < B.GetCols(); j++) {
      ASSERT_EQ(B(i, j), Expected(i, j));
    }
  }
}

TEST(operator_test, operator_plus_1) {
  MyMatrix A(2, 3);
  MyMatrix B(move(A));
  ASSERT_THROW(A + B, logic_error);
}

TEST(operator_test, operator_plus_2) {
  MyMatrix A(2, 3);
  MyMatrix B(3, 3);
  ASSERT_THROW(B + A, logic_error);
}

TEST(operator_test, operator_plus_3) {
  MyMatrix A(2, 3);
  MyMatrix B(2, 4);
  ASSERT_THROW(A + B, logic_error);
}

TEST(operator_test, operator_plus_4) {
  MyMatrix A(2, 3);
  A.initialize(-123);
  MyMatrix B(2, 3);
  B.initialize(123);
  MyMatrix C(2, 3);
  C.initialize(0);
  ASSERT_TRUE(C == A + B);
}

TEST(operator_test, operator_plus_5) {
  MyMatrix A(2, 3);
  A.initialize(0.1111111);
  MyMatrix B(2, 3);
  B.initialize(2.2222222);
  MyMatrix C(2, 3);
  C.initialize(2.3333333);
  ASSERT_TRUE(C == A + B);
}

TEST(operator_test, operator_minus_1) {
  MyMatrix A(2, 3);
  MyMatrix B(move(A));
  ASSERT_THROW(A - B, logic_error);
}

TEST(operator_test, operator_minus_2) {
  MyMatrix A(2, 3);
  MyMatrix B(3, 3);
  ASSERT_THROW(B - A, logic_error);
}

TEST(operator_test, operator_minus_3) {
  MyMatrix A(2, 3);
  MyMatrix B(2, 4);
  ASSERT_THROW(A - B, logic_error);
}

TEST(operator_test, operator_minus_4) {
  MyMatrix A(2, 3);
  A.initialize(-123);
  MyMatrix B(2, 3);
  B.initialize(123);
  MyMatrix C(2, 3);
  C.initialize(246);
  ASSERT_TRUE(C == B - A);
}

TEST(operator_test, operator_minus_5) {
  MyMatrix A(2, 3);
  A.initialize(0.1111111);
  MyMatrix B(2, 3);
  B.initialize(2.2222222);
  MyMatrix C(2, 3);
  C.initialize(2.1111111);
  ASSERT_TRUE(C == B - A);
}

TEST(operator_test, operator_mult_1) {
  MyMatrix A(2, 3);
  A.initialize(0.1111111);
  MyMatrix C(2, 3);
  C.initialize(0.5555555);
  ASSERT_TRUE(C == A * 5);
}

TEST(operator_test, operator_mult_2) {
  MyMatrix A(2, 3);
  A.initialize(0.1111111);
  MyMatrix C(2, 3);
  C.initialize(-0.3333333);
  ASSERT_TRUE(C == -3 * A);
}

TEST(operator_test, operator_mult_3) {
  MyMatrix A(3, 3);
  A.initialize(1);
  MyMatrix B(3, 3);
  B.initialize(2);
  MyMatrix C(3, 3);
  C.initialize(6);
  ASSERT_TRUE(C == A * B);
}

TEST(operator_test, operator_mult_4) {
  MyMatrix A(3, 3);
  MyMatrix B(4, 4);
  ASSERT_THROW(A * B, logic_error);
}

TEST(operator_test, operator_eq_eq_1) {
  MyMatrix A(2, 3);
  A.initialize(1.35657);
  MyMatrix B(A);
  ASSERT_TRUE(A == B);
}

TEST(operator_test, operator_eq_eq_2) {
  MyMatrix A(2, 3);
  A.initialize(7);
  MyMatrix B(1, 3);
  B.initialize(7);
  ASSERT_FALSE(A == B);
}

TEST(operator_test, operator_eq_1) {
  MyMatrix A(3, 5);
  MyMatrix B(2, 2);
  B = A;
  ASSERT_EQ(B.GetRows(), 3);
  ASSERT_EQ(B.GetCols(), 5);
}

TEST(operator_test, operator_eq_2) {
  MyMatrix A(3, 4);
  MyMatrix B(2, 2);
  MyMatrix C(5, 5);
  A = B = C;
  ASSERT_EQ(A.GetRows(), 5);
  ASSERT_EQ(A.GetCols(), 5);
  ASSERT_EQ(B.GetRows(), 5);
  ASSERT_EQ(B.GetCols(), 5);
}

TEST(operator_test, operator_plus_eq_1) {
  MyMatrix A(2, 3);
  A.initialize(0.1111111);
  MyMatrix B(2, 3);
  B.initialize(2.2222222);
  MyMatrix C(2, 3);
  C.initialize(2.3333333);
  B += A;
  ASSERT_TRUE(C == B);
}

TEST(operator_test, operator_minus_eq_1) {
  MyMatrix A(2, 3);
  A.initialize(0.1111111);
  MyMatrix B(2, 3);
  B.initialize(2.2222222);
  MyMatrix C(2, 3);
  C.initialize(2.1111111);
  B -= A;
  ASSERT_TRUE(C == B);
}

TEST(operator_test, operator_mult_eq_1) {
  MyMatrix A(2, 3);
  A.initialize(0.1111111);
  MyMatrix C(2, 3);
  C.initialize(0.5555555);
  A *= 5;
  ASSERT_TRUE(C == A);
}

TEST(operator_test, operator_mult_eq_2) {
  MyMatrix A(3, 3);
  A.initialize(1);
  MyMatrix B(3, 3);
  B.initialize(2);
  MyMatrix C(3, 3);
  C.initialize(6);
  A *= B;
  ASSERT_TRUE(C == A);
}

TEST(operator_test, operator_index_1) {
  MyMatrix A(3, 3);
  A.initialize(0);
  A(1, 1) = 1;
  ASSERT_EQ(A(1, 1), 1);
}

TEST(operator_test, operator_index_2) {
  MyMatrix A(1, 1);
  ASSERT_THROW(A(-2, 0) = 1, out_of_range);
}

TEST(operator_test, operator_index_3) {
  MyMatrix A(1, 1);
  ASSERT_THROW(A(0, -4) = 1, out_of_range);
}

TEST(operator_test, operator_index_4) {
  MyMatrix A(1, 1);
  ASSERT_THROW(A(2, 0) = 1, out_of_range);
}

TEST(operator_test, operator_index_5) {
  MyMatrix A(1, 1);
  ASSERT_THROW(A(0, 4) = 1, out_of_range);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}