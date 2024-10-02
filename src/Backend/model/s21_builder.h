#ifndef S21_BUILDER_H
#define S21_BUILDER_H

#include "./s21_model.h"

namespace s21 {
/**
 * @brief Абстрактный класс Builder
 */
class Builder {
 public:
  virtual void CreateModel() = 0;
  virtual ~Builder() = default;
};

/**
 * @brief Класс определеющий создание модели из файлов с расширением .obj
 */
class BuilderFromObjFile : public Builder {
 private:
  std::shared_ptr<ProductModel> model_ptr = nullptr;
  const char *file_name = nullptr;

 public:
  explicit BuilderFromObjFile(const char *file_name) : file_name(file_name) {}

  ~BuilderFromObjFile() = default;

  /**
   * @brief Сброс построенной модели
   */
  void Reset() noexcept {
    if (model_ptr != nullptr) model_ptr.reset();
  }
  /**
   * @brief Построение модели из переданного файла
   */
  void CreateModel() override;

  /**
   * @brief Геттер для класса
   * @return указатель на модель
   */
  std::shared_ptr<ProductModel> GetProductModel() const noexcept {
    return model_ptr;
  }

 private:
  /**
   * @brief Метод выполняющий первичный просмотр файла для инициализации всех
   * необходимых структур данных
   */
  void ObjCounter();
  /**
   * @brief Метод выполняющий валидацию и запись данных из файла в структуру
   * данных
   */
  void MatrixFill();
  /**
   * @brief метод определяющий минимум и максимум по каждой координате
   * @param vector_counter общее число вершин
   */
  void MinMax(int vector_counter);
};
}  // namespace s21

#endif  // S21_BUILDER_H