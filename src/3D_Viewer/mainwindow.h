#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMovie>
#include <QTimer>
#include <QtOpenGL/QtOpenGL>
#include <QtOpenGLWidgets/QtOpenGLWidgets>

#include "controller.h"
#include "gifimage/qgifimage.h"
#include "giflib/gif_lib.h"
#include "giflib/gif_lib_private.h"
#include "interactions.h"
#include "preferences.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  char *result_path = NULL;
  QString file = 0;
  int fileStatus = 0;

 public slots:
  void set_file(QString filename, size_t vert_count, size_t face_count);

 private slots:
  void on_pushButton_screen_clicked();
  void on_pushButton_gif_clicked();
  void makeGIF();
  void timerRun();

  void on_actionView_preferences_triggered();

  void on_actionModel_interactions_triggered();

 private:
  Ui::MainWindow *ui;
  QString file_name = "";
  QTimer *timer;
  QVector<QImage> gif;
  float count = 0;
  QMessageBox errorBox;
  s21::controller_facade *controller;
  s21::preferences *preferences_dialog = new s21::preferences(this);
  s21::interactions *interactions_dialog = new s21::interactions(this);
};

}  // namespace s21
#endif  // MAINWINDOW_H
