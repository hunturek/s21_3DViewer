#ifndef S21_MODEL_H
#define S21_MODEL_H

#include <memory>
#include <vector>

#include "../matrix/s21_matrix_oop.h"
#include "./s21_observer.h"

namespace s21 {

/**
 * @brief Класс определяющий модель объекта
 */
class ProductModel : public Subject {
 public:
  std::vector<std::vector<int>> facets{};
  S21Matrix matrix{};
  double range_x[2] = {};
  double range_y[2] = {};
  double range_z[2] = {};

  ProductModel() : matrix(1, 3) {}
  ~ProductModel() = default;

  /**
   * @brief Сдвиг модели на a по оси координат
   * @param a величина сдвига
   * @param flag координата сдвига
   */
  void Movement(const double a, const char flag) noexcept;

  /**
   * @brief Масштабирование в a раз
   * @param a величина масштабирования
   */
  void Mult(const double a);

  /**
   * @brief Вписать модель в рамку величиной f
   * @param f величина рамки
   */
  void ResizeFrames(const double f);

  /**
   * @brief Центрирование объекта
   */
  void CenterFrames() noexcept;

  /**
   * @brief Поворот на угол вокруг оси координат
   * @param angle величина угла поворота
   * @param flag по какой координате поворот
   */
  void Rot(double angle, const char flag) noexcept;
};

}  // namespace s21

#endif  // S21_MODEL_H