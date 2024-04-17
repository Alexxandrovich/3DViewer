#include "mainwindow.h"

#include <QBuffer>
#include <QMessageBox>
#include <QSettings>

#include "ui_mainwindow.h"

MainWindow::MainWindow(s21::controller *controller, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->glwidget->controller = controller;

  QObject::connect(ui->glwidget, SIGNAL(signalToMain(int, int)), this,
                   SLOT(getSignalGl(int, int)));

  QSettings mySettings;

  if (mySettings.value("flag_settings").toInt()) {
    ui->glwidget->color_background_red =
        mySettings.value("background_red").toDouble();
    ui->glwidget->color_background_green =
        mySettings.value("background_green").toDouble();
    ui->glwidget->color_background_blue =
        mySettings.value("background_blue").toDouble();

    ui->glwidget->flag_parallel = mySettings.value("flag_parallel").toInt();
    if (ui->glwidget->flag_parallel) {
      ui->radioButton_parallel->setChecked(true);
    } else {
      ui->radioButton_central->setChecked(true);
    }

    ui->glwidget->flag_edge_solid = mySettings.value("flag_edge_solid").toInt();
    if (ui->glwidget->flag_edge_solid) {
      ui->radioButton_solid_line->setChecked(true);
    } else {
      ui->radioButton_dash_line->setChecked(true);
    }

    ui->glwidget->flag_view_vertice =
        mySettings.value("flag_view_vertice").toInt();
    if (ui->glwidget->flag_view_vertice == 0) {
      ui->radioButton_none->setChecked(true);
    } else if (ui->glwidget->flag_view_vertice == 1) {
      ui->radioButton_circle->setChecked(true);
    } else {
      ui->radioButton_square->setChecked(true);
    }

    ui->glwidget->width_edge = mySettings.value("width_edge").toDouble();
    ui->horizontalSlider_width_edge->setValue(ui->glwidget->width_edge * 10);

    ui->glwidget->color_edge = mySettings.value("color_edge").value<QColor>();
    ui->glwidget->color_vertice =
        mySettings.value("color_vertice").value<QColor>();
    ui->glwidget->size_vertice = mySettings.value("size_vertice").toDouble();
    ui->horizontalSlider_size_vertice->setValue(ui->glwidget->size_vertice *
                                                10);
  }

  cmdHandler_ = new s21::CommandHandler(this);
}

MainWindow::~MainWindow() {
  QSettings mySettings;
  mySettings.setValue("background_red", ui->glwidget->color_background_red);
  mySettings.setValue("background_green", ui->glwidget->color_background_green);
  mySettings.setValue("background_blue", ui->glwidget->color_background_blue);

  mySettings.setValue("flag_parallel", ui->glwidget->flag_parallel);
  mySettings.setValue("flag_edge_solid", ui->glwidget->flag_edge_solid);
  mySettings.setValue("flag_view_vertice", ui->glwidget->flag_view_vertice);

  mySettings.setValue("width_edge", ui->glwidget->width_edge);
  mySettings.setValue("color_edge", ui->glwidget->color_edge);
  mySettings.setValue("color_vertice", ui->glwidget->color_vertice);

  mySettings.setValue("size_vertice", ui->glwidget->size_vertice);

  ui->glwidget->flag_settings = 1;
  mySettings.setValue("flag_settings", ui->glwidget->flag_settings);

  delete ui;
  delete cmdHandler_;
}

void MainWindow::on_pushButton_open_clicked() {
  QString file = QFileDialog::getOpenFileName(this, "", "", "", 0,
                                              QFileDialog::DontUseNativeDialog);
  int index = file.lastIndexOf('/');
  QString filename = file.mid(index + 1);
  ui->label_name->setText(filename);

  int index_dot = filename.indexOf('.');

  if (filename.mid(index_dot + 1) != "obj") {
    ui->label_name->setText("Select file .obj!");
  } else {
    std::string path = file.toStdString();

    ui->glwidget->controller->cSetData();
    ui->glwidget->controller->cParser(path);
    ui->glwidget->controller->cCenter();
    ui->glwidget->controller->cScaleInitial();

    ui->label_value_move_x->setText(QString::number(0));
    ui->label_value_move_y->setText(QString::number(0));
    ui->label_value_move_z->setText(QString::number(0));
    ui->label_value_x->setText(QString::number(0));
    ui->label_value_y->setText(QString::number(0));
    ui->label_value_z->setText(QString::number(0));
    ui->label_value_scale->setText(QString::number(1));

    ui->horizontalSliderScale->setValue(10);
    ui->horizontalSliderMove_X->setValue(0);
    ui->horizontalSliderMove_Y->setValue(0);
    ui->horizontalSliderMove_Z->setValue(0);
    ui->horizontalSliderX->setValue(0);
    ui->horizontalSliderY->setValue(0);
    ui->horizontalSliderZ->setValue(0);

    on_horizontalSliderX_valueChanged(0);
    on_horizontalSliderY_valueChanged(0);
    on_horizontalSliderZ_valueChanged(0);

    on_horizontalSliderMove_X_valueChanged(0);
    on_horizontalSliderMove_Y_valueChanged(0);
    on_horizontalSliderMove_Z_valueChanged(0);
    on_horizontalSliderScale_valueChanged(10);

    auto points = ui->glwidget->controller->cGetPoint();

    ui->label_vertices->setText(QString::number(points.size()));
    ui->label_edge->setText(QString::number(GetEdges()));

    auto polygons = ui->glwidget->controller->cGetPolygon();

    ui->glwidget->ct_pol = 4 * GetEdges();

    ui->glwidget->freeData();
    ui->glwidget->lines = new int[ui->glwidget->ct_pol];
    ui->glwidget->vertices = new double[3 * points.size()];

    ui->glwidget->update();
  }
}

void MainWindow::on_horizontalSliderX_valueChanged(int value) {
  ui->glwidget->angle_x = value - ui->label_value_x->text().toInt();
  ui->label_value_x->setText(QString::number(value));
  ui->glwidget->controller->cRotateXYZ(ui->glwidget->angle_x, 1, 0, 0);
  ui->glwidget->update();
  ui->horizontalSliderX->setSliderPosition(value);
}

void MainWindow::on_horizontalSliderY_valueChanged(int value) {
  ui->glwidget->angle_y = value - ui->label_value_y->text().toInt();
  ui->label_value_y->setText(QString::number(value));
  ui->glwidget->controller->cRotateXYZ(ui->glwidget->angle_y, 0, 1, 0);
  ui->glwidget->update();
  ui->horizontalSliderY->setSliderPosition(value);
}

void MainWindow::on_horizontalSliderZ_valueChanged(int value) {
  ui->glwidget->angle_z = value - ui->label_value_z->text().toInt();
  ui->label_value_z->setText(QString::number(value));
  ui->glwidget->controller->cRotateXYZ(ui->glwidget->angle_z, 0, 0, 1);
  ui->glwidget->update();
}

void MainWindow::on_horizontalSliderMove_X_valueChanged(int value) {
  ui->glwidget->move_x =
      value / 200.0 - ui->label_value_move_x->text().toDouble();
  ui->label_value_move_x->setText(QString::number(value / 200.0));
  ui->glwidget->controller->cMoveXYZ(ui->glwidget->move_x, 0, 0);
  ui->glwidget->update();
}

void MainWindow::on_horizontalSliderMove_Y_valueChanged(int value) {
  ui->glwidget->move_y =
      value / 200.0 - ui->label_value_move_y->text().toDouble();
  ui->label_value_move_y->setText(QString::number(value / 200.0));
  ui->glwidget->controller->cMoveXYZ(0, ui->glwidget->move_y, 0);
  ui->glwidget->update();
}

void MainWindow::on_horizontalSliderMove_Z_valueChanged(int value) {
  ui->glwidget->move_z =
      value / 200.0 - ui->label_value_move_z->text().toDouble();
  ui->label_value_move_z->setText(QString::number(value / 200.0));
  ui->glwidget->controller->cMoveXYZ(0, 0, ui->glwidget->move_z);
  ui->glwidget->update();
}

void MainWindow::on_horizontalSliderScale_valueChanged(int value) {
  ui->glwidget->scale = value / 10.0;
  ui->glwidget->controller->cScaleXYZ(ui->glwidget->scale,
                                      ui->label_value_scale->text().toDouble());
  ui->label_value_scale->setText(QString::number(value / 10.0));
  ui->glwidget->update();
}

void MainWindow::on_radioButton_parallel_clicked() {
  ui->glwidget->flag_parallel = 1;
  ui->glwidget->update();
}

void MainWindow::on_radioButton_central_clicked() {
  ui->glwidget->flag_parallel = 0;
  ui->glwidget->update();
}

void MainWindow::on_pushButton_edge_color_clicked() {
  ui->glwidget->color_edge = QColorDialog::getColor();
  ui->glwidget->update();
}

void MainWindow::on_radioButton_solid_line_clicked() {
  ui->glwidget->flag_edge_solid = 1;
  ui->glwidget->update();
}

void MainWindow::on_radioButton_dash_line_clicked() {
  ui->glwidget->flag_edge_solid = 0;
  ui->glwidget->update();
}

void MainWindow::on_pushButton_vertice_color_clicked() {
  ui->glwidget->color_vertice = QColorDialog::getColor();
  ui->glwidget->update();
}

void MainWindow::on_radioButton_none_clicked() {
  ui->glwidget->flag_view_vertice = 0;
  ui->glwidget->update();
}

void MainWindow::on_radioButton_circle_clicked() {
  ui->glwidget->flag_view_vertice = 1;
  ui->glwidget->update();
}

void MainWindow::on_radioButton_square_clicked() {
  ui->glwidget->flag_view_vertice = 2;
  ui->glwidget->update();
}

void MainWindow::on_pushButton_background_clicked() {
  QColor color = QColorDialog::getColor();
  ui->glwidget->color_background_red = color.redF();
  ui->glwidget->color_background_green = color.greenF();
  ui->glwidget->color_background_blue = color.blueF();
  ui->glwidget->update();
}

void MainWindow::on_horizontalSlider_width_edge_valueChanged(int value) {
  ui->glwidget->width_edge = value / 10.0;
  ui->glwidget->update();
}

void MainWindow::on_horizontalSlider_size_vertice_valueChanged(int value) {
  ui->glwidget->size_vertice = value / 10.0;
  ui->glwidget->update();
}

void MainWindow::on_pushButton_save_image_clicked() {
  cmdHandler_->handleCommand(0);
}

void MainWindow::on_pushButton_gif_clicked() { cmdHandler_->handleCommand(1); }

int MainWindow::GetEdges() {
  unsigned int edges = 0;
  auto polygons = ui->glwidget->controller->cGetPolygon();
  for (unsigned int j = 0; j < polygons.size(); j++) {
    edges += polygons[j].points.size();
  }
  return edges / 2;
}

void MainWindow::getSignalGl(int angle_x, int angle_y) {
  on_horizontalSliderX_valueChanged(angle_x);
  on_horizontalSliderY_valueChanged(angle_y);
}
