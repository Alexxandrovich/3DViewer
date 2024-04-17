#ifndef CPP4_3DVIEWER_V2_SRC_3DVIEWER_CONTROLLER_CONTROLLER_H_
#define CPP4_3DVIEWER_V2_SRC_3DVIEWER_CONTROLLER_CONTROLLER_H_

#include "s21_3d_viewer.h"

namespace s21 {

class controller {
 public:
  controller(Data *data = nullptr) { this->data_ = data ?: new Data(); }
  ~controller() { delete data_; }
  int cParser(const std::string &path);
  void cPrintPoints();
  void cPrintPolygons();

  void cMatrixTransformation(double transformation_matrix[][4], double *vector,
                             int i);
  void cCenter();
  void cScaleInitial();
  void cMoveXYZ(double sx, double sy, double sz);
  void cScaleXYZ(double scale_cur, double scale_prev);
  void cRotateXYZ(double angle, int x, int y, int z);

  std::vector<s21::Polygon> &cGetPolygon();
  std::vector<s21::Point> &cGetPoint();

  double *cGetMinMaxX();
  double *cGetMinMaxY();
  double *cGetMinMaxZ();

  void cSetData();

 protected:
  Data *data_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_SRC_3DVIEWER_CONTROLLER_CONTROLLER_H_
