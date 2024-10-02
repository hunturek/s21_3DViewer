/* Copyright [2024] <Casscurs> */

#ifndef DESKTOP_CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_HPP_
#define DESKTOP_CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_HPP_

#include <exception>
#include <iostream>
#include <utility>
#include <math.h>

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

 public:
  /* Конструкторы и деструктор*/
  S21Matrix() noexcept;
  explicit S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other) noexcept;
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix() noexcept;

  /* Acessors and Mutators */
  int get_rows() noexcept;
  int get_cols() noexcept;
  void set_rows(int otherRows);
  void set_cols(int otherCols);

  /* Операторы */
  S21Matrix& operator=(S21Matrix other);
  double& operator()(int i, int j);
  const double& operator()(int i, int j) const;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  friend S21Matrix operator+(S21Matrix matrix1, const S21Matrix& matrix2);
  friend S21Matrix operator-(S21Matrix matrix1, const S21Matrix& matrix2);
  friend S21Matrix operator*(S21Matrix matrix1, const S21Matrix& matrix2);
  friend S21Matrix operator*(S21Matrix matrix1, const double& num);
  friend S21Matrix operator*(const double& num, S21Matrix matrix1);
  bool operator==(const S21Matrix& other) const;

  /* Операции*/
  bool EqMatrix(const S21Matrix& other) const noexcept;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const noexcept;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

 private:
  /* Вспомогательные функции*/
  void freeMatrix();
  void cpyMatrix(const S21Matrix& other);
  void initMatrix();
  void swap(S21Matrix& other);
  bool float_compare(double a, double b) const;
  bool size_check(const S21Matrix& other) const;
  double Bareiss_algorith(const S21Matrix& buf) const;
  void find_minor(int i, int j, const S21Matrix& A, const S21Matrix& buf) const;
};

#endif  // DESKTOP_CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_HPP_
