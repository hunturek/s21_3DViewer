#include "display.h"

int display::static_number = 0;

display::display(QWidget *parent) : QOpenGLWidget(parent) {}

void display::Add(s21::Subject *subject) {
  this->subject = subject;
  this->subject->Attach(this);
  ++display::static_number;
  this->number = display::static_number;
  return;
}

/* При создании окна */
void display::initializeGL() { glEnable(GL_DEPTH_TEST); }

/* При изменении размеров окна */
void display::resizeGL(int w, int h) {
  /* Область видимости окна, где будет отрисовка */
  glViewport(0, 0, w, h);
}

void display::paintGL() {
  glLoadIdentity();

  if (projection == PARALLEL) {
    /* Работа с матрицей проекций */
    glMatrixMode(GL_PROJECTION);
    /* Задаем параллельную проецию */
    glOrtho(-1, 1, -1, 1, -10, 10);

  } else if (projection == CENTRAL) {
    /* Работа с матрицей проекций */
    glMatrixMode(GL_PROJECTION);
    /* Задаем центральную проецию */
    glFrustum(-1, 1, -1, 1, 2, 12.5);
    glTranslated(0, 0, -2.5);
  }
  if (file) {
    /* Цвет фона */
    glClearColor(back_color.x() / 255.0f, back_color.y() / 255.0f,
                 back_color.z() / 255.0f, 0);
    /* Очистка буфера цвета в каждом прогоне */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLineWidth(edges_size);
    drawCoordinateAxes();

    if (edges_type == DOTTED) {
      /* пунктир */
      glEnable(GL_LINE_STIPPLE);
      /* Первый параметр - фактор повторения, второй - паттерн */
      glLineStipple(10, 0xAAAA);
    } else if (edges_type == SOLID) {
      glDisable(GL_LINE_STIPPLE);
    }

    glColor3d(edge_color.x() / 255.0f, edge_color.y() / 255.0f,
              edge_color.z() / 255.0f);

    for (size_t i = 0; i < model_ptr->facets.size(); ++i) {
      glBegin(GL_LINE_LOOP);
      //  glColor3f(1.0f, 0.0f, 0.0f); //цвет отображения
      for (size_t j = 0; j < model_ptr->facets[i].size(); ++j) {
        int n = model_ptr->facets[i][j];
        glVertex3d(model_ptr->matrix(n, 0), model_ptr->matrix(n, 1),
                   model_ptr->matrix(n, 2));
      }
      glEnd();
    }

    if (vert_type == CIRCLE)
      glEnable(GL_POINT_SMOOTH);
    else
      glDisable(GL_POINT_SMOOTH);

    glColor3d(vert_color.x() / 255.0f, vert_color.y() / 255.0f,
              vert_color.z() / 255.0f);
    glPointSize(vert_size);  // размер элементов

    if (vert_type != 0) {
      glBegin(GL_POINTS);
      for (int i = 0; i < model_ptr->matrix.get_rows(); ++i) {
        glVertex3d(model_ptr->matrix(i, 0), model_ptr->matrix(i, 1),
                   model_ptr->matrix(i, 2));
      }
      glEnd();
    }
  }
}

void display::mousePressEvent(QMouseEvent *mo) { mPos = mo->pos(); }

void display::mouseMoveEvent(QMouseEvent *mo) {
  xRot = 0.005 / M_PI * (mo->pos().y() - mPos.y());
  yRot = 0.005 / M_PI * (mo->pos().x() - mPos.x());
  update();
}

void display::drawCoordinateAxes() {
  /* Ось X - Красная */
  glDisable(GL_LINE_STIPPLE);
  glColor3d(2.0, 0.0, 0.0);
  glBegin(GL_LINES);
  glVertex3d(-2.0, 0.0, 0.0);
  glVertex3d(2.0, 0.0, 0.0);
  glEnd();

  /* Ось Y - Зеленая */
  glColor3d(0.0, 2.0, 0.0);
  glBegin(GL_LINES);
  glVertex3d(0.0, -2.0, 0.0);
  glVertex3d(0.0, 2.0, 0.0);
  glEnd();

  /* Ось Z - Синяя */
  glColor3d(0.0, 0.0, 2.0);
  glBegin(GL_LINES);
  glVertex3d(0.0, 0.0, -2.0);
  glVertex3d(0.0, 0.0, 2.0);
  glEnd();
}
