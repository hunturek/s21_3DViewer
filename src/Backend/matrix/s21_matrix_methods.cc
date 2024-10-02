/* Copyright [2024] <Casscurs> */

#include "./s21_matrix_oop.h"

/* Конструктор по умолчанию */
S21Matrix::S21Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr) {}

/* Параметризованный конструктор */
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 0 || cols_ < 0) {
    throw std::invalid_argument("Incorrect matrix size");
  }
  this->initMatrix();
}

/* Конструктор копирования */
S21Matrix::S21Matrix(const S21Matrix& other) noexcept
    : S21Matrix(other.rows_, other.cols_) {
  this->cpyMatrix(other);
}

/* Конструктор перемещения */
S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

/* Деструктор */
S21Matrix::~S21Matrix() noexcept { freeMatrix(); }

/* Acessors */
int S21Matrix::get_rows() noexcept { return rows_; }
int S21Matrix::get_cols() noexcept { return cols_; }
/* Mutators */
void S21Matrix::set_rows(int otherRows) {
  if (otherRows < 0)
    throw std::length_error("matrix rows could not be negative");
  if (otherRows != rows_) {
    S21Matrix buf(otherRows, cols_);
    buf.cpyMatrix(*this);
    (*this).swap(buf);
  }
}
void S21Matrix::set_cols(int otherCols) {
  if (otherCols < 0)
    throw std::length_error("matrix cols could not be negative");
  if (otherCols != cols_) {
    S21Matrix buf(rows_, otherCols);
    buf.cpyMatrix(*this);
    (*this).swap(buf);
  }
}
