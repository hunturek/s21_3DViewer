#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "display.h"

namespace s21 {

int file_status_main = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      controller(new controller_facade(this)) {
  ui->setupUi(this);

  timer = new QTimer(0);

  controller->setOGLwidget(ui->openGLWidget);
  connect(this->controller, &controller_facade::set_settings,
          preferences_dialog, &preferences::set_settings);
  connect(this->controller, &controller_facade::set_file, this,
          &MainWindow::set_file);
  connect(this->ui->pushButton_openFile, &QPushButton::clicked,
          this->controller, &controller_facade::load_file);
  connect(this->ui->pushButton_reload, &QPushButton::clicked, this->controller,
          &controller_facade::reload_file);
  connect(this->timer, &QTimer::timeout, this, &MainWindow::timerRun);
}

MainWindow::~MainWindow() {
  delete preferences_dialog;
  delete interactions_dialog;
  controller->save_settings();
  delete ui;
}

void MainWindow::set_file(QString filename, size_t vert_count,
                          size_t face_count) {
  ui->label_filename->setText(filename);
  ui->label_vert->setText(QString("%1").arg(vert_count));
  ui->label_face->setText(QString("%1").arg(face_count));
}

void MainWindow::on_pushButton_screen_clicked() {
  QString screen_name =
      QFileDialog::getSaveFileName(this, "Save screen", "", "*.jpeg *.bmp");
  if (!screen_name.isEmpty()) {
    ui->openGLWidget->grab().save(screen_name);
  }
}

void MainWindow::on_pushButton_gif_clicked() {
  timer->start(100);
  timerRun();
  count = 0.0;
}

void MainWindow::timerRun() {
  ui->horizontalSlider_timer->setSliderPosition(count * 10);
  if (count <= 10.0) {
    gif.push_back(ui->openGLWidget->grab().toImage());
    count += 0.1;
  } else {
    makeGIF();
    timer->stop();
  }
}

void MainWindow::makeGIF() {
  QString gif_name =
      QFileDialog::getSaveFileName(this, "Save gif", "", tr("(*.gif)"));
  QGifImage gif_image(QSize(1200, 1200));
  gif_image.setDefaultDelay(100);

  for (QVector<QImage>::Iterator screen = gif.begin(); screen != gif.end();
       ++screen) {
    gif_image.addFrame(*screen);
  }
  gif_image.save(gif_name);
  gif.clear();
  count = 0.0;
}

void MainWindow::on_actionView_preferences_triggered() {
  connect(preferences_dialog, &preferences::projection, this->controller,
          &controller_facade::set_projection);
  connect(preferences_dialog, &preferences::edges, this->controller,
          &controller_facade::set_edges_type);
  connect(preferences_dialog, &preferences::vertices, this->controller,
          &controller_facade::set_vertices_type);
  connect(preferences_dialog, &preferences::size, this->controller,
          &controller_facade::set_size);
  connect(preferences_dialog, &preferences::color, this->controller,
          &controller_facade::set_color);
  preferences_dialog->show();
}

void MainWindow::on_actionModel_interactions_triggered() {
  connect(interactions_dialog, &interactions::move, this->controller,
          &controller_facade::move_model);
  connect(interactions_dialog, &interactions::rotate, this->controller,
          &controller_facade::rotate_model);
  connect(interactions_dialog, &interactions::scale, this->controller,
          &controller_facade::set_model_scale);
  interactions_dialog->show();
}

}  // namespace s21
