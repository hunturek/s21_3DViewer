/* Copyright [2024] <Casscurs> */

#include "./s21_matrix_oop.h"
#include <math.h>

void S21Matrix::freeMatrix() {
  for (int i = 0; i != rows_; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  matrix_ = nullptr;
}

void S21Matrix::cpyMatrix(const S21Matrix& other) {
  int minRows = std::min(rows_, other.rows_);
  int minCols = std::min(cols_, other.cols_);

  for (int i = 0; i != minRows; ++i) {
    for (int j = 0; j != minCols; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::initMatrix() {
  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; ++i) {
    try {
      matrix_[i] = new double[cols_]();
    } catch (const std::exception& ex) {
      for (int j = 0; j < i; ++j) {
        delete[] matrix_[j];
      }
      delete[] matrix_;
      throw;
    }
  }
}

void S21Matrix::swap(S21Matrix& other) {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
}

/* Вернет true, если числа равны, false - не равны */
bool S21Matrix::float_compare(double a, double b) const {
  return round(a * pow(10, 6)) == round(b * pow(10, 6)) ? true : false;
}

/* Вернет true, если размеры совпали */
bool S21Matrix::size_check(const S21Matrix& other) const {
  bool result = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    result = false;
  }
  return result;
}

/* Составление минора элемента матрицы*/
void S21Matrix::find_minor(int i, int j, const S21Matrix& A,
                           const S21Matrix& buf) const {
  int minRow = -1;
  for (int l = 0; l < A.rows_; ++l) {
    int minCol = 0;
    if (l != i) ++minRow;
    for (int n = 0; n < A.cols_; ++n) {
      if (l == i || n == j) {
        continue;
      } else {
        buf.matrix_[minRow][minCol] = A.matrix_[l][n];
        ++minCol;
      }
    }
  }
}
