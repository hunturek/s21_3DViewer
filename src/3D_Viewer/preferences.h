#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QVector3D>

namespace Ui {
class preferences;
}

namespace s21 {
/**
 * @brief класс диалогового окна настроек
 */
class preferences : public QDialog {
  Q_OBJECT

 public:
  explicit preferences(QWidget *parent = nullptr);
  ~preferences();

 public slots:
  void set_settings(int v_t, int e_t, int proj, float v_s, float e_s,
                    QVector3D v_c, QVector3D e_c, QVector3D b_c);

 signals:
  void projection(int projection);
  void vertices(int type);
  void edges(int type);
  void size(int object, float size);
  void color(int object, QVector3D rgb);

 private slots:
  void on_radioButton_parallel_proj_clicked();

  void on_radioButton_central_proj_clicked();

  void on_radioButton_typeEdge_solid_clicked();

  void on_radioButton_typeEdge_dotted_clicked();

  void on_radioButton_typeVert_none_clicked();

  void on_radioButton_typeVert_circle_clicked();

  void on_radioButton_typeVert_square_clicked();

  void on_doubleSpinBox_vertSize_valueChanged(double arg1);

  void on_doubleSpinBox_edgeSize_valueChanged(double arg1);

  void on_comboBox_colorVert_currentIndexChanged(int index);

  void on_spinBox_redVert_valueChanged(int arg1);

  void on_spinBox_greenVert_valueChanged(int arg1);

  void on_spinBox_blueVert_valueChanged(int arg1);

  void on_comboBox_colorEdge_currentIndexChanged(int index);

  void on_spinBox_redEdge_valueChanged(int arg1);

  void on_spinBox_greenEdge_valueChanged(int arg1);

  void on_spinBox_blueEdge_valueChanged(int arg1);

  void on_comboBox_colorBack_currentIndexChanged(int index);

  void on_spinBox_redBack_valueChanged(int arg1);

  void on_spinBox_greenBack_valueChanged(int arg1);

  void on_spinBox_blueBack_valueChanged(int arg1);

 private:
  Ui::preferences *ui;
  QVector3D rgb_color(int index);
  size_t str_color(QVector3D rgb_color);
};

}  // namespace s21
#endif  // PREFERENCES_H
