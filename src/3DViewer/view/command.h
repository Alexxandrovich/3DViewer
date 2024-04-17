#ifndef CPP4_3DVIEWER_V2_SRC_3DVIEWER_VIEW_COMMAND_H_
#define CPP4_3DVIEWER_V2_SRC_3DVIEWER_VIEW_COMMAND_H_

#include <QMainWindow>

#include "mainwindow.h"

class MainWindow;

namespace s21 {

class Command : public QMainWindow {
 public:
  virtual ~Command() {}
  virtual void execute() {}

 protected:
  MainWindow *mainWindow_;
};

class GifCommand : public Command {
  Q_OBJECT
 public:
  GifCommand(MainWindow *mainWindow) { mainWindow_ = mainWindow; }

  void execute();

 private slots:
  void makeGif();

 private:
  int frameCount_;
  QTimer *timer_;
  QImage images_[50];
};

class DownloadImageCommand : public Command {
 public:
  DownloadImageCommand(MainWindow *mainWindow) { mainWindow_ = mainWindow; }
  void execute();
};

class CommandHandler {
 public:
  CommandHandler(MainWindow *mainWindow) {
    buttonImage_ = new DownloadImageCommand(mainWindow);
    buttonGif_ = new GifCommand(mainWindow);
  }
  ~CommandHandler() {
    delete buttonImage_;
    delete buttonGif_;
  }

  void handleCommand(int commandMode);

 private:
  DownloadImageCommand *buttonImage_;
  GifCommand *buttonGif_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_SRC_3DVIEWER_VIEW_COMMAND_H_
