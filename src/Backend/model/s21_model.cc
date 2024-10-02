#include "./s21_model.h"

namespace s21 {

void ProductModel::Movement(const double a, const char flag) noexcept {
  switch (flag) {
    case 'x':
      for (int i = 0; i != matrix.get_rows(); ++i) matrix(i, 0) += a;
      break;
    case 'y':
      for (int i = 0; i != matrix.get_rows(); ++i) matrix(i, 1) += a;
      break;
    case 'z':
      for (int i = 0; i != matrix.get_rows(); ++i) matrix(i, 2) += a;
      break;
  }
  Notify();
}

void ProductModel::Mult(const double a) {
  this->matrix *= a;
  Notify();
}

void ProductModel::ResizeFrames(const double f) {
  double max = fabs(range_x[1] - range_x[0]);
  if (fabs(range_y[1] - range_y[0]) > max) max = fabs(range_y[1] - range_y[0]);
  if (fabs(range_z[1] - range_z[0]) > max) max = fabs(range_z[1] - range_z[0]);

  double scale = (f - (f * (-1))) / max;

  for (int i = 0; i < 2; ++i) {
    range_x[i] = range_x[i] * scale;
    range_y[i] = range_x[i] * scale;
    range_z[i] = range_x[i] * scale;
  }
  Mult(scale);
}

void ProductModel::CenterFrames() noexcept {
  double center_x = range_x[0] + (range_x[1] - range_x[0]) / 2;
  double center_y = range_y[0] + (range_y[1] - range_y[0]) / 2;
  double center_z = range_z[0] + (range_z[1] - range_z[0]) / 2;

  for (int i = 0; i != matrix.get_rows(); ++i) {
    matrix(i, 0) -= center_x;
    matrix(i, 1) -= center_y;
    matrix(i, 2) -= center_z;
  }
  Notify();
}

/*!
    \brief Поворот на угол по вокруг оси координат
*/

void ProductModel::Rot(double angle,
                       const char flag) noexcept {  // поворот по оси flag
  angle = angle * M_PI / 180;

  for (int i = 0; i != matrix.get_rows(); ++i) {
    double tmp_x = matrix(i, 0);
    double tmp_y = matrix(i, 1);
    double tmp_z = matrix(i, 2);

    switch (flag) {
      case 'x':
        matrix(i, 1) = cos(angle) * tmp_y - sin(angle) * tmp_z;
        matrix(i, 2) = sin(angle) * tmp_y + cos(angle) * tmp_z;
        break;
      case 'y':
        matrix(i, 0) = cos(angle) * tmp_x + sin(angle) * tmp_z;
        matrix(i, 2) = -sin(angle) * tmp_x + cos(angle) * tmp_z;
        break;
      case 'z':
        matrix(i, 0) = cos(angle) * tmp_x - sin(angle) * tmp_y;
        matrix(i, 1) = sin(angle) * tmp_x + cos(angle) * tmp_y;
        break;
    }
  }
  Notify();
}

}  // namespace s21