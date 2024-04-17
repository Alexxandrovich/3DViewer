#ifndef CPP4_3DVIEWER_V2_SRC_MODEL_S21_3D_VIEWER_H_
#define CPP4_3DVIEWER_V2_SRC_MODEL_S21_3D_VIEWER_H_

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace s21 {

struct Point {
  Point() {
    x = 0;
    y = 0;
    z = 0;
  }
  double x;
  double y;
  double z;
};

struct Polygon {
  Polygon() {}
  std::vector<int> points;
};

class Data {
 public:
  Data();
  int Parser(const std::string &path);
  void PrintPoints();
  void PrintPolygons();

  void MatrixTransformation(double transformation_matrix[][4], double *vector,
                            int i);
  void Center();
  void ScaleInitial();
  void MoveXYZ(double sx, double sy, double sz);
  void ScaleXYZ(double scale_cur, double scale_prev);
  void RotateXYZ(double angle, int x, int y, int z);
  std::vector<Polygon> &GetPolygon();
  std::vector<Point> &GetPoint();

  double *GetMinMaxX();
  double *GetMinMaxY();
  double *GetMinMaxZ();

 private:
  static const int kMax = 1000000;
  static const int kMin = -1000000;
  enum { kCorrectInput = 0, kIncorrectInput = 1 };

  void MinMax(int type, double value);
  int ParseV(const std::string &line);
  int ParseF(const std::string &line);

  double min_max_x_[2];
  double min_max_y_[2];
  double min_max_z_[2];
  std::vector<Polygon> polygons_;
  std::vector<Point> points_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_SRC_MODEL_S21_3D_VIEWER_H_
