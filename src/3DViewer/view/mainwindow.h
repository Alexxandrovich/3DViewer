#ifndef CPP4_3DVIEWER_V2_SRC_3DVIEWER_VIEW_MAINWINDOW_H_
#define CPP4_3DVIEWER_V2_SRC_3DVIEWER_VIEW_MAINWINDOW_H_

#include <qgifimage.h>

#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QTimer>

#include "command.h"
#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class CommandHandler;
class GifCommand;
class DownloadImageCommand;
}  // namespace s21

class gl_class;

class MainWindow : public QMainWindow {
  friend class s21::DownloadImageCommand;
  friend class s21::GifCommand;
  friend class s21::CommandHandler;
  friend class gl_class;
  Q_OBJECT

 public:
  MainWindow(s21::controller *controller, QWidget *parent = nullptr);
  ~MainWindow();

 public slots:
  void getSignalGl(int angle_x, int angle_y);

 private slots:
  void on_pushButton_open_clicked();

  void on_horizontalSliderX_valueChanged(int value);

  void on_horizontalSliderY_valueChanged(int value);

  void on_horizontalSliderZ_valueChanged(int value);

  void on_horizontalSliderMove_X_valueChanged(int value);

  void on_horizontalSliderMove_Y_valueChanged(int value);

  void on_horizontalSliderMove_Z_valueChanged(int value);

  void on_horizontalSliderScale_valueChanged(int value);

  void on_radioButton_parallel_clicked();

  void on_radioButton_central_clicked();

  void on_pushButton_edge_color_clicked();

  void on_radioButton_solid_line_clicked();

  void on_radioButton_dash_line_clicked();

  void on_pushButton_vertice_color_clicked();

  void on_radioButton_none_clicked();

  void on_radioButton_circle_clicked();

  void on_radioButton_square_clicked();

  void on_pushButton_background_clicked();

  void on_horizontalSlider_width_edge_valueChanged(int value);

  void on_horizontalSlider_size_vertice_valueChanged(int value);

  void on_pushButton_save_image_clicked();

  void on_pushButton_gif_clicked();

 private:
  int GetEdges();

  QTimer *timer;
  s21::CommandHandler *cmdHandler_;
  Ui::MainWindow *ui;
};

#endif  // CPP4_3DVIEWER_V2_SRC_3DVIEWER_VIEW_MAINWINDOW_H_
