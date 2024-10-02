/* Copyright [2024] <Casscurs> */

#include "./s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept {
  if (!size_check(other)) return false;

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (!float_compare(matrix_[i][j], other.matrix_[i][j])) {
        return false;
      }
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (!size_check(other)) throw std::invalid_argument("Incorrect matrix size");

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (!size_check(other)) throw std::invalid_argument("Incorrect matrix size");

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (this->rows_ != other.cols_)
    throw std::invalid_argument("Incorrect matrix size");

  S21Matrix result(this->rows_, other.cols_);

  for (int i = 0; i < result.rows_; ++i) {
    for (int j = 0; j < result.cols_; ++j) {
      for (int k = 0; k < other.rows_; ++k) {
        result.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  this->swap(result);
}

S21Matrix S21Matrix::Transpose() const noexcept {
  S21Matrix result(cols_, rows_);

  for (int i = 0; i < result.rows_; ++i) {
    for (int j = 0; j < result.cols_; ++j) {
      result.matrix_[i][j] = this->matrix_[j][i];
    }
  }
  return result;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) throw std::invalid_argument("Incorrect matrix size");
  if (this->rows_ == 1) return matrix_[0][0];
  return Bareiss_algorith(*this);
}

double S21Matrix::Bareiss_algorith(const S21Matrix& old) const {
  S21Matrix buf(old);
  /* Bareiss algorithm */
  double det = 1;
  for (int j = 0; j < buf.cols_; ++j) {
    int nonZero = j;
    /* Ищем строку с ненулевым элементом */
    for (int i = j; i < buf.rows_; ++i) {
      if (buf.matrix_[i][j] != 0) {
        nonZero = i;
        break;
      }
    }
    /* Поменяли строки местами */
    if (nonZero != j) {
      for (int k = 0; k < buf.cols_; ++k) {
        std::swap(buf.matrix_[j][k], buf.matrix_[nonZero][k]);
      }
      det = -det;
    }
    /* Проверка деления на ноль, если не прошли, то матрица вырожденная*/
    if (buf.matrix_[j][j] == 0) {
      det = 0;
      break;
    }
    /* Сведение к ступенчатому виду с помощью преобразования строк*/
    for (int i = j + 1; i < buf.rows_; ++i) {
      double corr = buf.matrix_[i][j] / buf.matrix_[j][j];
      for (int k = j; k < buf.rows_; ++k) {
        buf.matrix_[i][k] -= corr * buf.matrix_[j][k];
      }
    }
    det *= buf.matrix_[j][j];
  }
  if (fabs(det) < 1e-7) {
    det = 0;
  }
  return det;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) throw std::invalid_argument("Incorrect matrix size");
  if (rows_ == 1) return *this;
  S21Matrix result(rows_, cols_);
  S21Matrix buf(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      find_minor(i, j, *this, buf);
      result.matrix_[i][j] = buf.Determinant();
      if (((i + j) % 2 != 0) && (i + j != 0)) result.matrix_[i][j] *= -1;
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) throw std::invalid_argument("Incorrect matrix size");
  double det = Determinant();
  if (det == 0) throw std::logic_error("Determinant must be non-zero");
  S21Matrix result(rows_, cols_);
  if (rows_ > 1) {
    result = CalcComplements();
    result = result.Transpose();
    result.MulNumber(static_cast<double>(1) / det);
  } else {
    result.matrix_[0][0] = static_cast<double>(1) / this->matrix_[0][0];
  }
  return result;
}
