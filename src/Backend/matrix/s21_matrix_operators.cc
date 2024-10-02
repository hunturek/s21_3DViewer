/* Copyright [2024] <Casscurs> */

#include "./s21_matrix_oop.h"

S21Matrix& S21Matrix::operator=(S21Matrix other) {
  swap(other);
  return *this;
}

double& S21Matrix::operator()(int i, int j) {
  if (i < 0 || j < 0 || i >= rows_ || j >= cols_)
    throw std::length_error("incorrect index");
  return matrix_[i][j];
}

const double& S21Matrix::operator()(int i, int j) const {
  if (i < 0 || j < 0 || i >= rows_ || j >= cols_)
    throw std::length_error("incorrect index");
  return matrix_[i][j];
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}
S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

S21Matrix operator+(S21Matrix matrix1, const S21Matrix& matrix2) {
  matrix1 += matrix2;
  return matrix1;
}

S21Matrix operator-(S21Matrix matrix1, const S21Matrix& matrix2) {
  matrix1 -= matrix2;
  return matrix1;
}

S21Matrix operator*(S21Matrix matrix1, const S21Matrix& matrix2) {
  matrix1 *= matrix2;
  return matrix1;
}

S21Matrix operator*(S21Matrix matrix1, const double& num) {
  matrix1 *= num;
  return matrix1;
}

S21Matrix operator*(const double& num, S21Matrix matrix1) {
  matrix1 *= num;
  return matrix1;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}
