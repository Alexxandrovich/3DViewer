#include "s21_googletest.h"

TEST(S21TEST, Init) {
  const std::string path = "./tests/model.txt";
  s21::Data dataset;
  dataset.Parser(path);
  dataset.Center();
  dataset.ScaleInitial();

  std::vector<s21::Point> &points = dataset.GetPoint();

  for (unsigned int i = 0; i < points.size(); ++i) {
    EXPECT_DOUBLE_EQ(fabs(points[i].x), 1);
    EXPECT_DOUBLE_EQ(fabs(points[i].y), 1);
    EXPECT_DOUBLE_EQ(fabs(points[i].z), 1);
  }
}

TEST(S21TEST, Move) {
  const std::string path = "./tests/model.txt";
  s21::Data dataset;
  dataset.Parser(path);
  dataset.Center();
  dataset.ScaleInitial();

  dataset.MoveXYZ(143, 143, 143);
  std::vector<s21::Point> &points = dataset.GetPoint();

  EXPECT_DOUBLE_EQ(points[0].x, 144);
  EXPECT_DOUBLE_EQ(points[0].y, 142);
  EXPECT_DOUBLE_EQ(points[0].z, 142);

  dataset.MoveXYZ(-143, -143, -143);
  points = dataset.GetPoint();

  EXPECT_DOUBLE_EQ(points[0].x, 1);
  EXPECT_DOUBLE_EQ(points[0].y, -1);
  EXPECT_DOUBLE_EQ(points[0].z, -1);
}

TEST(S21TEST, Scale1) {
  const std::string path = "./tests/model.txt";
  s21::Data dataset;
  dataset.Parser(path);
  dataset.Center();
  dataset.ScaleInitial();

  dataset.ScaleXYZ(1.65, 1);
  dataset.ScaleXYZ(1, 0);
  std::vector<s21::Point> &points = dataset.GetPoint();

  for (unsigned int i = 0; i < points.size(); ++i) {
    EXPECT_DOUBLE_EQ(fabs(points[i].x), 1.65);
    EXPECT_DOUBLE_EQ(fabs(points[i].y), 1.65);
    EXPECT_DOUBLE_EQ(fabs(points[i].z), 1.65);
  }
}

TEST(S21TEST, Scale2) {
  const std::string path = "./tests/model.txt";
  s21::Data dataset;
  dataset.Parser(path);
  dataset.Center();
  dataset.ScaleInitial();

  dataset.ScaleXYZ(8.54, 1);
  std::vector<s21::Point> &points = dataset.GetPoint();
  for (unsigned int i = 0; i < points.size(); ++i) {
    EXPECT_DOUBLE_EQ(fabs(points[i].x), 8.54);
    EXPECT_DOUBLE_EQ(fabs(points[i].y), 8.54);
    EXPECT_DOUBLE_EQ(fabs(points[i].z), 8.54);
  }
}

TEST(S21TEST, Scale3) {
  const std::string path = "./tests/model.txt";
  s21::Data dataset;
  dataset.Parser(path);
  dataset.Center();
  dataset.ScaleInitial();

  dataset.ScaleXYZ(3, 1);
  std::vector<s21::Point> &points = dataset.GetPoint();
  for (unsigned int i = 0; i < points.size(); ++i) {
    EXPECT_DOUBLE_EQ(fabs(points[i].x), 3);
    EXPECT_DOUBLE_EQ(fabs(points[i].y), 3);
    EXPECT_DOUBLE_EQ(fabs(points[i].z), 3);
  }
}

TEST(S21TEST, Rotate) {
  const std::string path = "./tests/model.txt";
  s21::Data dataset;
  dataset.Parser(path);
  dataset.Center();
  dataset.ScaleInitial();

  dataset.RotateXYZ(90, 1, 0, 0);
  std::vector<s21::Point> &points = dataset.GetPoint();

  for (unsigned int i = 0; i < points.size(); ++i) {
    EXPECT_DOUBLE_EQ(fabs(points[i].x), 1);
    EXPECT_DOUBLE_EQ(fabs(points[i].y), 1);
    EXPECT_DOUBLE_EQ(fabs(points[i].z), 1);
  }

  dataset.RotateXYZ(90, 0, 1, 0);
  points = dataset.GetPoint();
  for (unsigned int i = 0; i < points.size(); ++i) {
    EXPECT_DOUBLE_EQ(fabs(points[i].x), 1);
    EXPECT_DOUBLE_EQ(fabs(points[i].y), 1);
    EXPECT_DOUBLE_EQ(fabs(points[i].z), 1);
  }

  dataset.RotateXYZ(90, 0, 0, 1);
  points = dataset.GetPoint();
  for (unsigned int i = 0; i < points.size(); ++i) {
    EXPECT_DOUBLE_EQ(fabs(points[i].x), 1);
    EXPECT_DOUBLE_EQ(fabs(points[i].y), 1);
    EXPECT_DOUBLE_EQ(fabs(points[i].z), 1);
  }

  dataset.RotateXYZ(-90, 1, 0, 0);
  points = dataset.GetPoint();
  for (unsigned int i = 0; i < points.size(); ++i) {
    EXPECT_DOUBLE_EQ(fabs(points[i].x), 1);
    EXPECT_DOUBLE_EQ(fabs(points[i].y), 1);
    EXPECT_DOUBLE_EQ(fabs(points[i].z), 1);
  }
}

TEST(S21TEST, Parser1) {
  std::string path = "./tests/ball.txt";
  s21::Data dataset;
  int res = dataset.Parser(path);
  std::vector<s21::Point> &points = dataset.GetPoint();

  EXPECT_EQ(res, 0);
  EXPECT_EQ(points.size(), 9667U);
}

TEST(S21TEST, Parser2) {
  std::string path = "./tests/cube.txt";
  s21::Data dataset;
  int res = dataset.Parser(path);
  EXPECT_EQ(res, 0);

  double *min_max_x = dataset.GetMinMaxX();
  EXPECT_EQ(min_max_x[0], 0);
  EXPECT_EQ(min_max_x[1], 1);
}

TEST(S21TEST, Parser3) {
  std::string path = "./tests/cube.txt";
  s21::Data dataset;
  int res = dataset.Parser(path);
  EXPECT_EQ(res, 0);

  auto polygons = dataset.GetPolygon();
  EXPECT_EQ(polygons.size(), 12U);
}

TEST(S21TEST, Parser4) {
  std::string path = "./tests/not_exist_file.txt";
  s21::Data dataset;
  int res = dataset.Parser(path);
  EXPECT_EQ(res, 1);
}

TEST(S21TEST, Parser5) {
  std::string path = "./tests/cessna.txt";
  s21::Data dataset;
  int res = dataset.Parser(path);
  EXPECT_EQ(res, 0);

  auto points = dataset.GetPoint();

  EXPECT_EQ(points.size(), 3745U);
  EXPECT_EQ(points[9].y, -4.743738);
}

TEST(S21TEST, Parser6) {
  std::string path = "./tests/helicopter.txt";
  s21::Data dataset;
  int res = dataset.Parser(path);
  EXPECT_EQ(res, 0);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
