#ifndef CPP4_3DVIEWER_V2_SRC_3DVIEWER_VIEW_GL_CLASS_H_
#define CPP4_3DVIEWER_V2_SRC_3DVIEWER_VIEW_GL_CLASS_H_

#define GL_SILENCE_DEPRECATION
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "mainwindow.h"
#include "strategy_options.h"

namespace s21 {
class StrategyOptProjection;
class StrategyOptVertices;
class StrategyOptEdges;
class Parallel;
class Central;
class CircleVertices;
class SquareVertices;
class SolidEdge;
class DashEdge;
}  // namespace s21

class gl_class : public QOpenGLWidget, public QOpenGLFunctions {
  friend class MainWindow;
  Q_OBJECT

 public:
  explicit gl_class(QWidget *parent = nullptr);
  ~gl_class() = default;
  void freeData();
  void setOption(s21::StrategyOptProjection &opt);
  void setOption(s21::StrategyOptVertices &opt);
  void setOption(s21::StrategyOptEdges &opt);

  s21::controller *controller;

  int angle_x = 0;
  int angle_y = 0;
  int angle_z = 0;

  double fixed_angle_x_ = 0.0;
  double fixed_angle_y_ = 0.0;

  double move_x = 0;
  double move_y = 0;
  double move_z = 0;

  double scale = 1;

  int flag_parallel = 1;
  int flag_edge_solid = 1;
  double width_edge = 3;
  QColor color_edge = Qt::black;

  QColor color_vertice = Qt::black;
  int flag_view_vertice = 0;
  double size_vertice = 0;

  double color_background_red = 0.92549;
  double color_background_green = 0.925475;
  double color_background_blue = 0.92549;

  int flag_settings = 0;
  int flag_time = 0;

  double *vertices = nullptr;
  int *lines = nullptr;
  unsigned long ct_pol = 0;
  unsigned long ct_points = 0;

  int size = 2;
  int far = 50;
  float alpha = M_PI / 3;
  float near = size / (2 * tan(alpha / 2));

 signals:
  void signalToMain(int angle_x, int angle_y);

 protected:
  void initializeGL() override;
  void paintGL() override;
  void projectionSelect();
  void dataToPtr();
  void drawVertices();
  void drawPolygons();

  s21::StrategyOptProjection *opt_projection;
  s21::StrategyOptVertices *opt_vertices;
  s21::StrategyOptEdges *opt_edges;

 private:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

  QPointF mousePosition_;
  int rotationInited_;
};

#endif  // CPP4_3DVIEWER_V2_SRC_3DVIEWER_VIEW_GL_CLASS_H_
