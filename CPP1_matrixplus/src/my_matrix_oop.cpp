#include "my_matrix_oop.h"
using namespace std;

MyMatrix::MyMatrix() {
  rows_ = 3;
  cols_ = 3;
  matrix_ = new double *[rows_];

  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
}

MyMatrix::MyMatrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 1 || cols < 1) {
    throw invalid_argument("Number of rows and cols must be more than 0");
  }
  matrix_ = new double *[rows_];

  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
}

MyMatrix::MyMatrix(const MyMatrix &other) : MyMatrix(other.rows_, other.cols_) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

MyMatrix::MyMatrix(MyMatrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

MyMatrix::~MyMatrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
      matrix_[i] = nullptr;
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

int MyMatrix::GetRows() { return rows_; }

int MyMatrix::GetCols() { return cols_; }

void MyMatrix::SetRows(const int new_rows) {
  if (new_rows < 1) {
    throw invalid_argument("Number of rows and cols must be more than 0");
  }
  if (rows_ != new_rows) {
    int choose;
    MyMatrix other(new_rows, cols_);
    other.initialize(0);
    if (rows_ > new_rows) {
      choose = new_rows;
    } else if (rows_ < new_rows) {
      choose = rows_;
    }
    for (int i = 0; i < choose; i++) {
      for (int j = 0; j < cols_; j++) {
        other.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = other;
    rows_ = new_rows;
  }
}

void MyMatrix::SetCols(const int new_cols) {
  if (new_cols < 1) {
    throw invalid_argument("Number of rows and cols must be more than 0");
  }
  if (cols_ != new_cols) {
    int choose;
    MyMatrix other(rows_, new_cols);
    other.initialize(0);
    if (cols_ > new_cols) {
      choose = new_cols;
    } else if (cols_ < new_cols) {
      choose = cols_;
    }
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < choose; j++) {
        other.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = other;
    cols_ = new_cols;
  }
}

bool MyMatrix::EqMatrix(const MyMatrix &other) {
  bool result = true;
  if (!IsValid() || !other.IsValid()) {
    throw(logic_error("Incorrect matrix"));
  }
  if (rows_ != other.rows_ || cols_ != other.cols_) result = false;
  for (int i = 0; i < rows_ && result == true; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(other.matrix_[i][j] - matrix_[i][j]) > EPS) result = false;
    }
  }
  return result;
}

void MyMatrix::SumMatrix(const MyMatrix &other) {
  if (!IsValid() || !other.IsValid()) {
    throw(logic_error("Incorrect matrix"));
  }
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw(logic_error("Matrix sizes are not equal"));
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void MyMatrix::SubMatrix(const MyMatrix &other) {
  if (!IsValid() || !other.IsValid()) {
    throw(logic_error("Incorrect matrix"));
  }
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw(logic_error("Matrix sizes are not equal"));
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void MyMatrix::MulNumber(const double num) {
  if (!IsValid()) {
    throw(logic_error("Incorrect matrix"));
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void MyMatrix::MulMatrix(const MyMatrix &other) {
  if (!IsValid() || !other.IsValid()) {
    throw(logic_error("Incorrect matrix"));
  }
  if (cols_ != other.rows_) {
    throw(
        logic_error("Amount of columns in first matrix must be equal to amount "
                    "of rows in second matrix"));
  }

  MyMatrix result(rows_, other.cols_);
  result.initialize(0);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = result;
}

MyMatrix MyMatrix::Transpose() {
  if (!IsValid()) {
    throw(logic_error("Incorrect matrix"));
  }
  MyMatrix result(cols_, rows_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}

double MyMatrix::Determinant() {
  if (!IsValid()) {
    throw(logic_error("Incorrect matrix"));
  }
  if (cols_ != rows_) {
    throw(logic_error("Matrix must be square"));
  }
  double result = 0.0;

  if (rows_ == 1) result = matrix_[0][0];
  if (rows_ == 2)
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  if (rows_ > 2) {
    for (int i = 0; i < rows_; i++) {
      MyMatrix smaller_matrix;
      smaller_matrix = delete_row_and_col(i, 0);
      result += matrix_[i][0] * pow(-1, i) * smaller_matrix.Determinant();
    }
  }
  return result;
}

MyMatrix MyMatrix::CalcComplements() {
  if (!IsValid()) {
    throw(logic_error("Incorrect matrix"));
  }
  if (cols_ != rows_) {
    throw(logic_error("Matrix must be square"));
  }

  MyMatrix result(rows_, cols_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      MyMatrix smaller_matrix;
      smaller_matrix = delete_row_and_col(i, j);
      result.matrix_[i][j] = pow(-1, i + j) * smaller_matrix.Determinant();
    }
  }
  return result;
}

MyMatrix MyMatrix::InverseMatrix() {
  if (!IsValid()) {
    throw(logic_error("Incorrect matrix"));
  }
  if (Determinant() == 0) {
    throw(
        logic_error("Deteminant is equal to 0: Inverse matrix doesn't exist"));
  }
  MyMatrix result(rows_, cols_);
  result = CalcComplements();
  result = result.Transpose();
  result.MulNumber(1 / Determinant());
  return result;
}

MyMatrix MyMatrix::operator+(const MyMatrix &other) {
  MyMatrix result(*this);
  result += other;
  return result;
}

MyMatrix MyMatrix::operator-(const MyMatrix &other) {
  MyMatrix result(*this);
  result -= other;
  return result;
}

MyMatrix MyMatrix::operator*(const MyMatrix &other) {
  MyMatrix result(*this);
  result *= other;
  return result;
}

MyMatrix operator*(const double num, MyMatrix other) {
  MyMatrix result(other);
  result *= num;
  return result;
}

MyMatrix operator*(MyMatrix other, const double num) {
  MyMatrix result(other);
  result *= num;
  return result;
}

bool MyMatrix::operator==(const MyMatrix &other) { return EqMatrix(other); }

MyMatrix &MyMatrix::operator=(const MyMatrix &other) {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;

  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }

  return *this;
}

void MyMatrix::operator+=(const MyMatrix &other) { SumMatrix(other); }

void MyMatrix::operator-=(const MyMatrix &other) { SubMatrix(other); }

void MyMatrix::operator*=(const double num) { MulNumber(num); };

void MyMatrix::operator*=(const MyMatrix &other) { MulMatrix(other); };

double &MyMatrix::operator()(int i, int j) {
  if (i < 0 || j < 0 || i >= rows_ || j >= cols_) {
    throw(out_of_range("Index is out of range"));
  }
  return matrix_[i][j];
}

void MyMatrix::initialize(double number) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = number;
    }
  }
}

bool MyMatrix::IsValid() const { return matrix_ != nullptr; }

MyMatrix MyMatrix::delete_row_and_col(int row, int col) {
  MyMatrix temp(rows_ - 1, cols_ - 1);

  for (int i = 0, a = 0; i < rows_; i++) {
    if (i != row) {
      for (int j = 0, b = 0; j < cols_; j++) {
        if (j != col) {
          temp.matrix_[a][b] = matrix_[i][j];
          b++;
        }
      }
      a++;
    }
  }
  return temp;
}