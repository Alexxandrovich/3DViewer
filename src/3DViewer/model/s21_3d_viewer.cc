#include "s21_3d_viewer.h"

namespace s21 {

Data::Data() {
  min_max_x_[0] = kMax;
  min_max_y_[0] = kMax;
  min_max_z_[0] = kMax;
  min_max_x_[1] = kMin;
  min_max_y_[1] = kMin;
  min_max_z_[1] = kMin;
}

void Data::MinMax(int type, double value) {
  switch (type) {
    case 1: {
      if (min_max_x_[0] > value) min_max_x_[0] = value;
      if (min_max_x_[1] < value) min_max_x_[1] = value;
      break;
    }
    case 2: {
      if (min_max_y_[0] > value) min_max_y_[0] = value;
      if (min_max_y_[1] < value) min_max_y_[1] = value;
      break;
    }
    case 3:
      if (min_max_z_[0] > value) min_max_z_[0] = value;
      if (min_max_z_[1] < value) min_max_z_[1] = value;
      break;
  }
}

int Data::ParseV(const std::string &line) {
  Point point;
  std::string::size_type pos = 1U;
  std::string::size_type sz = 0;
  int vr = Data::kCorrectInput;
  try {
    point.x = std::stod(line.substr(pos), &sz);
    MinMax(1, point.x);
    pos += sz;
    point.y = std::stod(line.substr(pos), &sz);
    MinMax(2, point.y);
    pos += sz;
    point.z = std::stod(line.substr(pos));
    MinMax(3, point.z);
    points_.push_back(point);
  } catch (...) {
    vr = Data::kIncorrectInput;
  }

  return vr;
}

int Data::ParseF(const std::string &line) {
  int pr = Data::kCorrectInput;
  std::string::size_type pos = 1U;
  std::string::size_type sz = 0;
  Polygon polygon;
  try {
    while (line.find_first_of("0123456789", pos) != std::string::npos) {
      polygon.points.push_back(std::stoi(line.substr(pos), &sz));
      pos += sz;
      while (line[pos] != '\0' && line[pos] != ' ') {
        ++pos;
      }
    }
    polygons_.push_back(polygon);
  } catch (...) {
    pr = Data::kIncorrectInput;
  }

  return pr;
}

int Data::Parser(const std::string &path) {
  int return_code = Data::kCorrectInput;
  std::ifstream fin(path);

  if (fin.is_open()) {
    std::string line;

    int ver_res = Data::kCorrectInput;
    int pol_res = Data::kCorrectInput;
    while (std::getline(fin, line) && pol_res == 0 && ver_res == 0) {
      if (line[0] == 'v' && line[1] == ' ') {
        ver_res = ParseV(line);
      } else if (line[0] == 'f') {
        pol_res = ParseF(line);
      }
    }

    fin.close();
    return_code =
        pol_res == Data::kCorrectInput && ver_res == Data::kCorrectInput
            ? Data::kCorrectInput
            : Data::kIncorrectInput;
  } else
    return_code = Data::kIncorrectInput;

  return return_code;
}

void Data::PrintPoints() {
  printf("File contains the following points:\n");
  for (unsigned int i = 0; i < points_.size(); ++i) {
    printf("%d point\n", i);
    printf("%lf ", points_[i].x);
    printf("%lf ", points_[i].y);
    printf("%lf \n", points_[i].z);
  }
  printf("Min X value:%f\n", min_max_x_[0]);
  printf("Max X value:%f\n", min_max_x_[1]);
  printf("Min Y value:%f\n", min_max_y_[0]);
  printf("Max Y value:%f\n", min_max_y_[1]);
  printf("Min Z value:%f\n", min_max_z_[0]);
  printf("Max Z value:%f\n", min_max_z_[1]);
}

void Data::PrintPolygons() {
  printf("File contains the following polygons:\n");
  for (unsigned int i = 0; i < polygons_.size(); ++i) {
    printf("%d polygon contains points indexes:\n", i);
    for (unsigned int j = 0; j < polygons_[i].points.size(); ++j)
      printf("%d ", polygons_[i].points[j]);
    printf("\n");
  }
}

void Data::MatrixTransformation(double transformation_matrix[][4],
                                double *vector, int i) {
  double res[4] = {0};

  res[0] += transformation_matrix[0][0] * vector[0] +
            transformation_matrix[0][1] * vector[1] +
            transformation_matrix[0][2] * vector[2];
  res[1] += transformation_matrix[1][0] * vector[0] +
            transformation_matrix[1][1] * vector[1] +
            transformation_matrix[1][2] * vector[2];
  res[2] += transformation_matrix[2][0] * vector[0] +
            transformation_matrix[2][1] * vector[1] +
            transformation_matrix[2][2] * vector[2];

  points_[i].x = res[0];
  points_[i].y = res[1];
  points_[i].z = res[2];
}

void Data::Center() {
  double center_x = min_max_x_[0] + (min_max_x_[1] - min_max_x_[0]) / 2;
  double center_y = min_max_y_[0] + (min_max_y_[1] - min_max_y_[0]) / 2;
  double center_z = min_max_z_[0] + (min_max_z_[1] - min_max_z_[0]) / 2;
  for (unsigned int i = 0; i < points_.size(); ++i) {
    points_[i].x -= center_x;
    points_[i].y -= center_y;
    points_[i].z -= center_z;
  }
}
void Data::ScaleInitial() {
  double x = min_max_x_[1] - min_max_x_[0];
  double y = min_max_y_[1] - min_max_y_[0];
  double z = min_max_z_[1] - min_max_z_[0];
  double dmax = 0;
  if (x >= y) {
    dmax = x;
  } else {
    dmax = y;
  }
  if (dmax < z) dmax = z;
  double value = 1;
  double scale = (value - value * (-1)) / dmax;
  for (unsigned int i = 0; i < points_.size(); ++i) {
    points_[i].x *= scale;
    points_[i].y *= scale;
    points_[i].z *= scale;
  }
}

void Data::MoveXYZ(double sx, double sy, double sz) {
  for (unsigned int i = 0; i < points_.size(); ++i) {
    points_[i].x += sx;
    points_[i].y += sy;
    points_[i].z += sz;
  }
}

void Data::ScaleXYZ(double scale_cur, double scale_prev) {
  if (scale_cur > 0 && scale_prev > 0) {
    for (unsigned int i = 0; i < points_.size(); ++i) {
      points_[i].x = scale_cur / scale_prev * (points_[i].x);
      points_[i].y = scale_cur / scale_prev * (points_[i].y);
      points_[i].z = scale_cur / scale_prev * (points_[i].z);
    }
  }
}

void Data::RotateXYZ(double angle, int x, int y, int z) {
  double radians = angle * M_PI / 180.0;
  double vector[4] = {0, 0, 0, 0};
  double x_trans_matrix[4][4] = {{1, 0, 0, 0},
                                 {0, cos(radians), -sin(radians), 0},
                                 {0, sin(radians), cos(radians), 0},
                                 {0, 0, 0, 1}};
  double y_trans_matrix[4][4] = {{cos(radians), 0, sin(radians), 0},
                                 {0, 1, 0, 0},
                                 {-sin(radians), 0, cos(radians), 0},
                                 {0, 0, 0, 1}};
  double z_trans_matrix[4][4] = {{cos(radians), -sin(radians), 0, 0},
                                 {sin(radians), cos(radians), 0, 0},
                                 {0, 0, 1, 0},
                                 {0, 0, 0, 1}};
  for (unsigned int i = 0; i < points_.size(); ++i) {
    vector[0] = points_[i].x;
    vector[1] = points_[i].y;
    vector[2] = points_[i].z;
    vector[3] = 1;
    if (x) {
      MatrixTransformation(x_trans_matrix, vector, i);
    } else if (y) {
      MatrixTransformation(y_trans_matrix, vector, i);
    } else if (z) {
      MatrixTransformation(z_trans_matrix, vector, i);
    }
  }
}

std::vector<Polygon> &Data::GetPolygon() { return polygons_; }

std::vector<Point> &Data::GetPoint() { return points_; }

double *Data::GetMinMaxX() { return min_max_x_; }

double *Data::GetMinMaxY() { return min_max_y_; }

double *Data::GetMinMaxZ() { return min_max_z_; }

}  // namespace s21
