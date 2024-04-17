#include "controller.h"

void s21::controller::cSetData() { this->data_ = new Data(); }

int s21::controller::cParser(const std::string &path) {
  return this->data_->Parser(path);
}

void s21::controller::cPrintPoints() { this->data_->PrintPoints(); }

void s21::controller::cPrintPolygons() { this->data_->PrintPolygons(); }

void s21::controller::cMatrixTransformation(double transformation_matrix[][4],
                                            double *vector, int i) {
  this->data_->MatrixTransformation(transformation_matrix, vector, i);
}

void s21::controller::cCenter() { this->data_->Center(); }

void s21::controller::cScaleInitial() { this->data_->ScaleInitial(); }

void s21::controller::cMoveXYZ(double sx, double sy, double sz) {
  this->data_->MoveXYZ(sx, sy, sz);
}

void s21::controller::cScaleXYZ(double scale_cur, double scale_prev) {
  this->data_->ScaleXYZ(scale_cur, scale_prev);
}

void s21::controller::cRotateXYZ(double angle, int x, int y, int z) {
  this->data_->RotateXYZ(angle, x, y, z);
}

std::vector<s21::Polygon> &s21::controller::cGetPolygon() {
  return this->data_->GetPolygon();
}

std::vector<s21::Point> &s21::controller::cGetPoint() {
  return this->data_->GetPoint();
}

double *s21::controller::cGetMinMaxX() { return this->data_->GetMinMaxX(); }

double *s21::controller::cGetMinMaxY() { return this->data_->GetMinMaxY(); }

double *s21::controller::cGetMinMaxZ() { return this->data_->GetMinMaxZ(); }
