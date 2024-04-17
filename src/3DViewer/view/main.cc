#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::controller *controller = new s21::controller;
  MainWindow w(controller);
  w.setWindowTitle("3DViewer v2.0");
  w.show();
  return a.exec();
}
