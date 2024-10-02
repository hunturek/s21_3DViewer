#ifndef DISPLAY_H
#define DISPLAY_H

#define NONE 0
#define SOLID 1
#define DOTTED 2

#define CIRCLE 1
#define SQUARE 2

#define CENTRAL 0
#define PARALLEL 1

#define GL_SILENCE_DEPRECATION
#include <QTime>
#include <QVector3D>
#include <QWidget>
#include <QtOpenGL>
#include <QtOpenGLWidgets>

#include "../Backend/model/s21_model.h"
#include "../Backend/model/s21_observer.h"

/**
 * @brief Класс специализирующийся на отрисовке модели
 */
class display : public QOpenGLWidget, public s21::IObserver {
  Q_OBJECT

 private:
  s21::Subject *subject = nullptr;
  /* общее число наблюдателей */
  static int static_number;
  /* номер конкретного наблюдателя */
  int number;

 private:
  double xRot = 0, yRot = 0, zRot = 0;
  double scale = 0;
  QPoint mPos;
  QTimer tmr;

  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;

  /**
   * @brief Метод необходимый для создания активного окна
   */
  void initializeGL() override;
  /**
   * @brief Метод меняющий область видимости окна при изменении размеров окна
   */
  void resizeGL(int w, int h) override;
  /**
   * @brief Метод отрисовывающий модель
   */
  void paintGL() override;
  /**
   * @brief Метод отрисовывающий координатные оси
   */
  void drawCoordinateAxes();

 public:
  QVector3D back_color = {0.0f, 0.0f, 0.0f};
  QVector3D vert_color = {255.0f, 255.0f, 255.0f};
  QVector3D edge_color = {255.0f, 255.0f, 255.0f};

  int edges_type = 0;
  float edges_size = 0.5;
  int vert_type = 0;
  float vert_size = 0.5;
  int projection = PARALLEL;

  bool file = 0;

  display(QWidget *parent);
  std::shared_ptr<s21::ProductModel> model_ptr = nullptr;

 public:
  virtual ~display() = default;

  /**
   * @brief Метод добавляющий объект наблюдения
   */
  void Add(s21::Subject *subject);

  /**
   * @brief Метод, который использует субъект для уведомления наблюдателя
   */
  void Update() override { update(); }

  /**
   * @brief Метод открепляющий наблядателя от субъекта наблюдения
   */
  void RemoveMeFromTheList() { subject->Detach(this); }
};

#endif  // DISPLAY_H
