#include "controller.h"

namespace s21 {

void controller::load_file() {
  QString file =
      QFileDialog::getOpenFileName(0, "Выберите файл", ".", tr("(*.obj)"));
  QByteArray q_path = file.toLocal8Bit();
  const char *filename = q_path.data();
  s21::BuilderFromObjFile build(filename);

  try {
    build.CreateModel();

    model_ptr = build.GetProductModel();

    QStringList list = file.split('/');
    widget->model_ptr = model_ptr;
    emit set_file(list.at(list.size() - 1), model_ptr->matrix.get_rows(),
                  model_ptr->facets.size());
    load_settings();

    widget->file = 1;
    widget->Add(&(*model_ptr));
    model_ptr->Attach(widget);

    widget->model_ptr->CenterFrames();
    widget->model_ptr->ResizeFrames(1);
  } catch (...) {
    emit set_file(QString("File error!"), 0, 0);
  }
}

void controller::reload_file() {
  model_ptr.reset();
  load_file();
}

void controller::set_central_projection() {
  widget->projection = CENTRAL;
  widget->update();
}

void controller::set_parallel_projection() {
  widget->projection = PARALLEL;
  widget->update();
}

void controller::set_vertices_type_none() {
  widget->vert_type = 0;
  widget->update();
}

void controller::set_vertices_type_circle() {
  widget->vert_type = CIRCLE;
  widget->update();
}

void controller::set_vertices_type_square() {
  widget->vert_type = SQUARE;
  widget->update();
}

void controller::set_vertices_size(float size) {
  widget->vert_size = size;
  widget->update();
}

void controller::set_vertices_color_rgb(float red, float green, float blue) {
  widget->vert_color.setX(red);
  widget->vert_color.setY(green);
  widget->vert_color.setZ(blue);
  widget->update();
}

void controller::set_edges_type_solid() {
  widget->edges_type = SOLID;
  widget->update();
}

void controller::set_edges_type_dotted() {
  widget->edges_type = DOTTED;
  widget->update();
}

void controller::set_edges_size(float size) {
  widget->edges_size = size;
  widget->update();
}

void controller::set_edges_color_rgb(float red, float green, float blue) {
  widget->edge_color.setX(red);
  widget->edge_color.setY(green);
  widget->edge_color.setZ(blue);
  widget->update();
}

void controller::set_background_color_rgb(float red, float green, float blue) {
  widget->back_color.setX(red);
  widget->back_color.setY(green);
  widget->back_color.setZ(blue);
  widget->update();
}

void controller::set_model_scale(float scale) {
  if (model_ptr) {
    if (scale < 0) {
      scale = -scale;
      scale = 1.0 / scale;
    }

    model_ptr->Mult(scale);
  }
}

void controller::move_model_x(float movement) {
  if (model_ptr) model_ptr->Movement(movement, 'x');
}

void controller::move_model_y(float movement) {
  if (model_ptr) model_ptr->Movement(movement, 'y');
}

void controller::move_model_z(float movement) {
  if (model_ptr) model_ptr->Movement(movement, 'z');
}

void controller::rotate_model_x(float angle) {
  if (model_ptr) model_ptr->Rot(angle, 'x');
}

void controller::rotate_model_y(float angle) {
  if (model_ptr) model_ptr->Rot(angle, 'y');
}

void controller::rotate_model_z(float angle) {
  if (model_ptr) model_ptr->Rot(angle, 'z');
}

void controller::save_settings() {
  // init
  settings->setValue("settings_exist", 1);

  // for verticles
  settings->setValue("vert_r", widget->vert_color.x());
  settings->setValue("vert_g", widget->vert_color.y());
  settings->setValue("vert_b", widget->vert_color.z());
  settings->setValue("verticles type", widget->vert_type);
  settings->setValue("verticles size", widget->vert_size);

  // for edges
  settings->setValue("edge_r", widget->edge_color.x());
  settings->setValue("edge_g", widget->edge_color.y());
  settings->setValue("edge_b", widget->edge_color.z());
  settings->setValue("line type", widget->edges_type);
  settings->setValue("line size", widget->edges_size);

  // for background
  settings->setValue("background_color_red", widget->back_color.x());
  settings->setValue("background_color_green", widget->back_color.y());
  settings->setValue("background_color_blue", widget->back_color.z());

  // for projection type
  settings->setValue("projection_type", widget->projection);
  // for file
  // settings->setValue("baseFile", file);
}

void controller::load_settings() {
  // if where was init of settings before else nothing
  int v_t, e_t, proj;
  float v_s, e_s;
  QVector3D v_c, e_c, b_c;
  if (settings->value("settings_exist").toInt()) {
    // For Verticles
    int vert_type = settings->value("verticles type").toInt();
    switch (vert_type) {
      case 0:
        v_t = 0;
        widget->vert_type = 0;
        break;
      case 1:
        v_t = 1;
        widget->vert_type = CIRCLE;
        break;
      case 2:
        v_t = 2;
        widget->vert_type = SQUARE;
        break;
    }
    widget->vert_size = settings->value("verticles size").toDouble();
    v_s = widget->vert_size;
    widget->vert_color.setX(settings->value("vert_r").toDouble());
    widget->vert_color.setY(settings->value("vert_g").toDouble());
    widget->vert_color.setZ(settings->value("vert_b").toDouble());

    v_c = widget->vert_color;
    // for file

    // For EDGES
    int edges_type = settings->value("line type").toInt();
    switch (edges_type) {
      case 1:
        e_t = 0;
        widget->edges_type = SOLID;
        break;
      case 2:
        e_t = 1;
        widget->edges_type = DOTTED;
        break;
    }
    widget->edges_size = settings->value("line size").toInt();
    e_s = widget->edges_size;
    widget->edge_color.setX(settings->value("edge_r").toDouble());
    widget->edge_color.setY(settings->value("edge_g").toDouble());
    widget->edge_color.setZ(settings->value("edge_b").toDouble());

    e_c = widget->edge_color;

    // For BACKGROUND
    widget->back_color.setX(settings->value("background_color_red").toDouble());
    widget->back_color.setY(
        settings->value("background_color_green").toDouble());
    widget->back_color.setZ(
        settings->value("background_color_blue").toDouble());

    b_c = widget->back_color;

    // For projection type
    widget->projection = settings->value("projection_type").toInt();
    proj = widget->projection;

    emit set_settings(v_t, e_t, proj, v_s, e_s, v_c, e_c, b_c);

    widget->update();
  }
}

controller_facade::controller_facade(QObject *parent) : controller(parent) {}

controller::controller(QObject *parent) : QObject(parent) {
  settings = new QSettings("school21", "TechnoTeam", this);
}

void controller::setOGLwidget(display *display) { widget = display; }

controller::controller() : QObject(nullptr) {}

}  // namespace s21
