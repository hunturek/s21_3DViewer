#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QOpenGLWidget>
#include <QSettings>
#include <QVector3D>

#include "../Backend/model/s21_builder.h"
#include "../Backend/model/s21_model.h"
#include "display.h"

namespace s21 {
/**
 * @brief класс контроллера-прослойки
 */
class controller : public QObject {
  Q_OBJECT

 public:
  controller();
  explicit controller(QObject *parent = nullptr);

  void setOGLwidget(display *display);
  std::shared_ptr<s21::ProductModel> model_ptr = nullptr;

 protected slots:
  /**
   * @brief загрузка файла и заполнение модели
   */
  void load_file();
  /**
   * @brief перезагрузка файла и заполнение модели
   */
  void reload_file();

 protected:
  /**
   * @brief установка центральной проекции
   */
  void set_central_projection();
  /**
   * @brief установка параллельной проекции
   */
  void set_parallel_projection();
  /**
   * @brief установка типа узлов none
   */
  void set_vertices_type_none();
  /**
   * @brief установка типа узлов circle
   */
  void set_vertices_type_circle();
  /**
   * @brief установка типа узлов square
   */
  void set_vertices_type_square();
  /**
   * @brief установка размера узлов
   */
  void set_vertices_size(float size);
  /**
   * @brief установка цвета узлов в rgb
   */
  void set_vertices_color_rgb(float red, float green, float blue);
  /**
   * @brief установка типа граней solid
   */
  void set_edges_type_solid();
  /**
   * @brief установка типа узлов dotted
   */
  void set_edges_type_dotted();
  /**
   * @brief установка размера узлов
   */
  void set_edges_size(float size);
  /**
   * @brief установка цвета узлов
   */
  void set_edges_color_rgb(float red, float green, float blue);
  /**
   * @brief установка цвета заднего фона
   */
  void set_background_color_rgb(float red, float green, float blue);
  /**
   * @brief установка масштаба модели
   */
  void set_model_scale(float scale);
  /**
   * @brief перемещение модели по оси x
   * @param movement рассотяние перемещения
   */
  void move_model_x(float movement);
  /**
   * @brief перемещение модели по оси y
   * @param movement рассотяние перемещения
   */
  void move_model_y(float movement);
  /**
   * @brief перемещение модели по оси z
   * @param movement рассотяние перемещения
   */
  void move_model_z(float movement);
  /**
   * @brief вращение модели вокруг оси x
   * @param angle угол вращения
   */
  void rotate_model_x(float angle);
  /**
   * @brief вращение модели вокруг оси y
   * @param angle угол вращения
   */
  void rotate_model_y(float angle);
  /**
   * @brief вращение модели вокруг оси z
   * @param angle угол вращения
   */
  void rotate_model_z(float angle);

  /**
   * @brief сохранение настроек
   */
  void save_settings();
  /**
   * @brief загрузка настроек
   */
  void load_settings();
  QSettings *settings;

 signals:
  void set_settings(int v_t, int e_t, int proj, float v_s, float e_s,
                    QVector3D v_c, QVector3D e_c, QVector3D b_c);
  void set_file(QString filename, size_t vert_count, size_t face_count);

 private:
  display *widget = nullptr;
};

/**
 * @brief класс фасада контроллера
 */
class controller_facade : public controller {
  Q_OBJECT

 public:
  explicit controller_facade(QObject *parent = nullptr);
  using controller::load_file;
  using controller::load_settings;
  using controller::reload_file;
  using controller::save_settings;
  using controller::set_model_scale;

 public slots:
  /**
   * @brief общая функция установки проекции модели
   * @param projection проекция, которая будет установлена
   */
  inline void set_projection(
      int projection) {  // inline потому что их можно писать в .h
    if (projection == 0) {
      set_central_projection();
    } else if (projection == 1) {
      set_parallel_projection();
    }
  };
  /**
   * @brief общая функция установки типа отрисовки вершин
   * @param type тип отрисовки, который будет установлен
   */
  inline void set_vertices_type(int type) {
    if (type == 0) {
      set_vertices_type_none();
    } else if (type == 1) {
      set_vertices_type_circle();
    } else if (type == 2) {
      set_vertices_type_square();
    }
  };
  /**
   * @brief общая функция установки типа отрисовки граней
   * @param type тип отрисовки, который будет установлен
   */
  inline void set_edges_type(int type) {
    if (type == 0) {
      set_edges_type_solid();
    } else if (type == 1) {
      set_edges_type_dotted();
    }
  };
  /**
   * @brief общая функция установки цвета в rgb
   * @param object объект, у которого будет изменен цвет
   * @param rgb вектор цветов
   */
  inline void set_color(int object, QVector3D rgb) {
    if (object == 0) {
      set_vertices_color_rgb(rgb.x(), rgb.y(), rgb.z());
    } else if (object == 1) {
      set_edges_color_rgb(rgb.x(), rgb.y(), rgb.z());
    } else if (object == 2) {
      set_background_color_rgb(rgb.x(), rgb.y(), rgb.z());
    }
  };
  /**
   * @brief общая функция установки размера отрисовки
   * @param object объект, у которого будет изменен размер отрисовки
   * @param size размер, на который будет изменен прошлый размер отрисовки
   */
  inline void set_size(int object, float size) {
    if (object == 0) {
      set_vertices_size(size);
    } else if (object == 1) {
      set_edges_size(size);
    }
  };
  /**
   * @brief общая функция перемещения модели
   * @param axis ось, вдоль которой будет происходить перемещение
   * @param movement количество перемещения
   */
  inline void move_model(int axis, float movement) {
    if (axis == 0) {
      move_model_x(movement);
    } else if (axis == 1) {
      move_model_y(movement);
    } else if (axis == 2) {
      move_model_z(movement);
    }
  }
  /**
   * @brief общая функция вращения модели
   * @param axis ось, вокруг которой будет происходить вращение
   * @param angle количество вращения
   */
  inline void rotate_model(int axis, float angle) {
    if (axis == 0) {
      rotate_model_x(angle);
    } else if (axis == 1) {
      rotate_model_y(angle);
    } else if (axis == 2) {
      rotate_model_z(angle);
    }
  }
};

}  // namespace s21
#endif  // CONTROLLER_H
