#include "preferences.h"

#include "ui_preferences.h"

namespace s21 {

preferences::preferences(QWidget *parent)
    : QDialog(parent), ui(new Ui::preferences) {
  ui->setupUi(this);
  this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

preferences::~preferences() { delete ui; }

void preferences::set_settings(int v_t, int e_t, int proj, float v_s, float e_s,
                               QVector3D v_c, QVector3D e_c, QVector3D b_c) {
  if (v_t == 0) {
    ui->radioButton_typeVert_none->setChecked(true);
    ui->radioButton_typeVert_circle->setChecked(false);
    ui->radioButton_typeVert_square->setChecked(false);
  } else if (v_t == 1) {
    ui->radioButton_typeVert_none->setChecked(false);
    ui->radioButton_typeVert_circle->setChecked(true);
    ui->radioButton_typeVert_square->setChecked(false);
  } else if (v_t == 2) {
    ui->radioButton_typeVert_none->setChecked(false);
    ui->radioButton_typeVert_circle->setChecked(false);
    ui->radioButton_typeVert_square->setChecked(true);
  }

  if (e_t == 0) {
    ui->radioButton_typeEdge_solid->setChecked(true);
    ui->radioButton_typeEdge_dotted->setChecked(false);
  } else if (e_t == 1) {
    ui->radioButton_typeEdge_solid->setChecked(false);
    ui->radioButton_typeEdge_dotted->setChecked(true);
  }

  if (proj == 0) {
    ui->radioButton_central_proj->setChecked(true);
    ui->radioButton_parallel_proj->setChecked(false);
  } else if (proj == 1) {
    ui->radioButton_central_proj->setChecked(false);
    ui->radioButton_parallel_proj->setChecked(true);
  }

  ui->doubleSpinBox_vertSize->setValue(v_s);
  ui->doubleSpinBox_edgeSize->setValue(e_s);

  ui->spinBox_redVert->setValue(v_c.x());
  ui->spinBox_greenVert->setValue(v_c.y());
  ui->spinBox_blueVert->setValue(v_c.z());

  ui->comboBox_colorVert->setCurrentIndex(str_color(v_c));

  ui->spinBox_redEdge->setValue(e_c.x());
  ui->spinBox_greenEdge->setValue(e_c.y());
  ui->spinBox_blueEdge->setValue(e_c.z());

  ui->comboBox_colorEdge->setCurrentIndex(str_color(e_c));

  ui->spinBox_redBack->setValue(b_c.x());
  ui->spinBox_greenBack->setValue(b_c.y());
  ui->spinBox_blueBack->setValue(b_c.z());

  ui->comboBox_colorBack->setCurrentIndex(str_color(b_c));
}

void preferences::on_radioButton_parallel_proj_clicked() { emit projection(1); }

void preferences::on_radioButton_central_proj_clicked() { emit projection(0); }

void preferences::on_radioButton_typeEdge_solid_clicked() { emit edges(0); }

void preferences::on_radioButton_typeEdge_dotted_clicked() { emit edges(1); }

void preferences::on_radioButton_typeVert_none_clicked() { emit vertices(0); }

void preferences::on_radioButton_typeVert_circle_clicked() { emit vertices(1); }

void preferences::on_radioButton_typeVert_square_clicked() { emit vertices(2); }

void preferences::on_doubleSpinBox_vertSize_valueChanged(double arg1) {
  emit size(0, arg1);
}

void preferences::on_doubleSpinBox_edgeSize_valueChanged(double arg1) {
  emit size(1, arg1);
}

void preferences::on_comboBox_colorVert_currentIndexChanged(int index) {
  emit color(0, rgb_color(index));
  ui->spinBox_redVert->setValue(rgb_color(index).x());
  ui->spinBox_greenVert->setValue(rgb_color(index).y());
  ui->spinBox_blueVert->setValue(rgb_color(index).z());
}

void preferences::on_spinBox_redVert_valueChanged(int arg1) {
  QVector3D rgb(arg1, ui->spinBox_greenVert->value(),
                ui->spinBox_blueVert->value());
  emit color(0, rgb);
}

void preferences::on_spinBox_greenVert_valueChanged(int arg1) {
  QVector3D rgb(ui->spinBox_redVert->value(), arg1,
                ui->spinBox_blueVert->value());
  emit color(0, rgb);
}

void preferences::on_spinBox_blueVert_valueChanged(int arg1) {
  QVector3D rgb(ui->spinBox_redVert->value(), ui->spinBox_greenVert->value(),
                arg1);
  emit color(0, rgb);
}

void preferences::on_comboBox_colorEdge_currentIndexChanged(int index) {
  emit color(1, rgb_color(index));
  ui->spinBox_redEdge->setValue(rgb_color(index).x());
  ui->spinBox_greenEdge->setValue(rgb_color(index).y());
  ui->spinBox_blueEdge->setValue(rgb_color(index).z());
}

void preferences::on_spinBox_redEdge_valueChanged(int arg1) {
  QVector3D rgb(arg1, ui->spinBox_greenEdge->value(),
                ui->spinBox_blueEdge->value());
  emit color(1, rgb);
}

void preferences::on_spinBox_greenEdge_valueChanged(int arg1) {
  QVector3D rgb(ui->spinBox_redEdge->value(), arg1,
                ui->spinBox_blueEdge->value());
  emit color(1, rgb);
}

void preferences::on_spinBox_blueEdge_valueChanged(int arg1) {
  QVector3D rgb(ui->spinBox_redEdge->value(), ui->spinBox_greenEdge->value(),
                arg1);
  emit color(1, rgb);
}

void preferences::on_comboBox_colorBack_currentIndexChanged(int index) {
  emit color(2, rgb_color(index));
  ui->spinBox_redBack->setValue(rgb_color(index).x());
  ui->spinBox_greenBack->setValue(rgb_color(index).y());
  ui->spinBox_blueBack->setValue(rgb_color(index).z());
}

void preferences::on_spinBox_redBack_valueChanged(int arg1) {
  QVector3D rgb(arg1, ui->spinBox_greenBack->value(),
                ui->spinBox_blueBack->value());
  emit color(2, rgb);
}

void preferences::on_spinBox_greenBack_valueChanged(int arg1) {
  QVector3D rgb(ui->spinBox_redBack->value(), arg1,
                ui->spinBox_blueBack->value());
  emit color(2, rgb);
}

void preferences::on_spinBox_blueBack_valueChanged(int arg1) {
  QVector3D rgb(ui->spinBox_redBack->value(), ui->spinBox_greenBack->value(),
                arg1);
  emit color(2, rgb);
}

QVector3D preferences::rgb_color(int index) {
  if (index == 4)
    return QVector3D(0, 0, 255);
  else if (index == 1)
    return QVector3D(0, 0, 0);
  else if (index == 2)
    return QVector3D(255, 0, 0);
  else if (index == 3)
    return QVector3D(0, 255, 0);
  else
    return QVector3D(255, 255, 255);
}

size_t preferences::str_color(QVector3D rgb_color) {
  if (rgb_color.x() == 0 && rgb_color.y() == 0 && rgb_color.z() == 255)
    return 4;
  else if (rgb_color.x() == 0 && rgb_color.y() == 0 && rgb_color.z() == 0)
    return 1;
  else if (rgb_color.x() == 255 && rgb_color.y() == 0 && rgb_color.z() == 0)
    return 2;
  else if (rgb_color.x() == 0 && rgb_color.y() == 255 && rgb_color.z() == 0)
    return 3;
  else
    return 0;
}

}  // namespace s21
