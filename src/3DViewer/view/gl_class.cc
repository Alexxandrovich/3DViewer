#include "gl_class.h"

#include <cmath>

gl_class::gl_class(QWidget *parent) : QOpenGLWidget{parent} {}

void gl_class::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(0.92549, 0.925475, 0.92549, 1);
}

void gl_class::paintGL() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClearColor(color_background_red, color_background_green,
               color_background_blue, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  projectionSelect();
  dataToPtr();

  glEnableVertexAttribArray(0);
  glEnableClientState(GL_VERTEX_ARRAY);

  glVertexPointer(3, GL_DOUBLE, 0, vertices);

  drawVertices();
  drawPolygons();

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableVertexAttribArray(0);
}

void gl_class::freeData() {
  delete[] vertices;
  delete[] lines;
}

void gl_class::projectionSelect() {
  s21::Parallel parallel;
  s21::Central central;

  if (flag_parallel)
    setOption(parallel);
  else
    setOption(central);

  opt_projection->projection(*this);
}

void gl_class::dataToPtr() {
  auto polygons = controller->cGetPolygon();
  auto points = controller->cGetPoint();

  ct_points = points.size();
  unsigned long int k = 0;
  for (unsigned long int i = 0; i < ct_points; i++) {
    vertices[k] = points[i].x;
    vertices[k + 1] = points[i].y;
    vertices[k + 2] = points[i].z;
    k = k + 3;
  }
  k = 0;
  int pol1 = 0;
  for (unsigned long int i = 0; i < polygons.size(); i++) {
    if (polygons[i].points[0] >= 0)
      pol1 = polygons[i].points[0] - 1;
    else
      pol1 = points.size() + polygons[i].points[0];
    lines[k++] = pol1;
    for (unsigned long int j = 1; j < polygons[i].points.size(); ++j) {
      if (polygons[i].points[j] >= 0) {
        lines[k++] = polygons[i].points[j] - 1;
        lines[k++] = polygons[i].points[j] - 1;
      } else {
        lines[k++] = points.size() + polygons[i].points[j];
        lines[k++] = points.size() + polygons[i].points[j];
      }
    }
    lines[k++] = pol1;
  }
}

void gl_class::drawVertices() {
  s21::CircleVertices circleVertices;
  s21::SquareVertices squareVertices;

  if (flag_view_vertice) {
    if (flag_view_vertice == 1)
      setOption(circleVertices);
    else
      setOption(squareVertices);

    opt_vertices->optionVertices(*this);
    glDrawArrays(GL_POINTS, 0, ct_points);
  }
}

void gl_class::drawPolygons() {
  s21::SolidEdge solidEdge;
  s21::DashEdge dashEdge;

  if (!flag_edge_solid)
    setOption(dashEdge);
  else
    setOption(solidEdge);

  opt_edges->optionEdge(*this);
  glDrawElements(GL_LINES, ct_pol, GL_UNSIGNED_INT, lines);
}

void gl_class::setOption(s21::StrategyOptProjection &opt) {
  opt_projection = &opt;
}

void gl_class::setOption(s21::StrategyOptVertices &opt) { opt_vertices = &opt; }

void gl_class::setOption(s21::StrategyOptEdges &opt) { opt_edges = &opt; }

void gl_class::mousePressEvent(QMouseEvent *event) {
  if (event->buttons() & Qt::LeftButton) {
    rotationInited_ = 1;
    mousePosition_ = event->position();
  } else if (event->buttons() & Qt::RightButton) {
    angle_x = 0;
    angle_y = 0;
    emit signalToMain(angle_x, angle_y);
  }
}

void gl_class::mouseMoveEvent(QMouseEvent *event) {
  if (rotationInited_) {
    fixed_angle_x_ = angle_x;
    fixed_angle_y_ = angle_y;
    rotationInited_ = 0;
  }
  angle_x = fixed_angle_x_ + 1 / M_PI * (event->pos().y() - mousePosition_.y());
  angle_y = fixed_angle_y_ + 1 / M_PI * (event->pos().x() - mousePosition_.x());

  emit signalToMain(angle_x, angle_y);
}
