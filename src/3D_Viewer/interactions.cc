#include "interactions.h"

#include "ui_interactions.h"

namespace s21 {

interactions::interactions(QWidget *parent)
    : QDialog(parent), ui(new Ui::interactions) {
  ui->setupUi(this);
  this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

interactions::~interactions() { delete ui; }

void interactions::on_pushButton_move_clicked() {
  if (ui->radioButton_moveX->isChecked())
    emit move(0, ui->doubleSpinBox_move->value());
  if (ui->radioButton_moveY->isChecked())
    emit move(1, ui->doubleSpinBox_move->value());
  if (ui->radioButton_moveZ->isChecked())
    emit move(2, ui->doubleSpinBox_move->value());
}

void interactions::on_pushButton_rotate_clicked() {
  if (ui->radioButton_rotateX->isChecked())
    emit rotate(0, ui->spinBox_rotate->value());
  if (ui->radioButton_rotateY->isChecked())
    emit rotate(1, ui->spinBox_rotate->value());
  if (ui->radioButton_rotateZ->isChecked())
    emit rotate(2, ui->spinBox_rotate->value());
}

void s21::interactions::on_pushButton_scale_clicked() {
  emit scale(ui->doubleSpinBox_scale->value());
}

}  // namespace s21
