#include "strategy_options.h"

namespace s21 {
void Parallel::projection(gl_class &gl) {
  int size = gl.size;
  int far = gl.far;
  glOrtho(-size, size, -size, size, -far, far);
}

void Central::projection(gl_class &gl) {
  int size = gl.size;
  int far = gl.far;
  int near = gl.near;
  glFrustum(-size, size, -size, size, near, far);
}

void NoneVertices::optionVertices(gl_class &gl) { gl.flag_view_vertice = 0; }

void CircleVertices::optionVertices(gl_class &gl) {
  gl.flag_view_vertice = 1;
  glColor3f(gl.color_vertice.redF(), gl.color_vertice.greenF(),
            gl.color_vertice.blueF());
  glPointSize(gl.size_vertice);
  glEnable(GL_POINT_SMOOTH);
}

void SquareVertices::optionVertices(gl_class &gl) {
  gl.flag_view_vertice = 2;
  glColor3f(gl.color_vertice.redF(), gl.color_vertice.greenF(),
            gl.color_vertice.blueF());
  glPointSize(gl.size_vertice);
  glDisable(GL_POINT_SMOOTH);
}

void SolidEdge::optionEdge(gl_class &gl) {
  glLineWidth(gl.width_edge);
  glColor3f(gl.color_edge.redF(), gl.color_edge.greenF(),
            gl.color_edge.blueF());
  glDisable(GL_LINE_SMOOTH);
  glDisable(GL_LINE_STIPPLE);
}

void DashEdge::optionEdge(gl_class &gl) {
  glLineWidth(gl.width_edge);
  glColor3f(gl.color_edge.redF(), gl.color_edge.greenF(),
            gl.color_edge.blueF());
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_LINE_STIPPLE);
  glLineStipple(2, 53007);
}
}  // namespace s21
