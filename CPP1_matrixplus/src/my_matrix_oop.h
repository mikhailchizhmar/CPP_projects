#ifndef __MYMATRIX_H__
#define __MYMATRIX_H__

#include <cmath>
#include <exception>
#include <iostream>

#define EPS 1e-7

class MyMatrix {
 private:
  int rows_, cols_;
  double** matrix_;

 public:
  MyMatrix();
  MyMatrix(int rows, int cols);
  MyMatrix(const MyMatrix& other);
  MyMatrix(MyMatrix&& other);
  ~MyMatrix();

  int GetRows();
  int GetCols();
  void SetRows(const int new_rows);
  void SetCols(const int new_cols);

  bool EqMatrix(const MyMatrix& other);
  void SumMatrix(const MyMatrix& other);
  void SubMatrix(const MyMatrix& other);
  void MulNumber(const double num);
  void MulMatrix(const MyMatrix& other);
  MyMatrix Transpose();
  MyMatrix CalcComplements();
  double Determinant();
  MyMatrix InverseMatrix();

  MyMatrix operator+(const MyMatrix& other);
  MyMatrix operator-(const MyMatrix& other);
  MyMatrix operator*(const MyMatrix& other);
  friend MyMatrix operator*(const double num, MyMatrix other);
  friend MyMatrix operator*(MyMatrix other, const double num);
  bool operator==(const MyMatrix& other);
  MyMatrix& operator=(const MyMatrix& other);
  void operator+=(const MyMatrix& other);
  void operator-=(const MyMatrix& other);
  void operator*=(const double num);
  void operator*=(const MyMatrix& other);
  double& operator()(int i, int j);

  void initialize(double number);
  bool IsValid() const;
  MyMatrix delete_row_and_col(int row, int col);
};

#endif