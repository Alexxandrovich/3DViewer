#include "command.h"

#include "ui_mainwindow.h"

namespace s21 {

void CommandHandler::handleCommand(int commandMode) {
  if (commandMode == 0) {
    buttonImage_->execute();
  } else {
    buttonGif_->execute();
  }
}

void GifCommand::execute() {
  frameCount_ = 0;
  timer_ = new QTimer();
  connect(timer_, SIGNAL(timeout()), this, SLOT(makeGif()));
  timer_->start(100);
}

void GifCommand::makeGif() {
  QGifImage gif;
  if (frameCount_ == 50) {
    timer_->stop();
    disconnect(timer_);
    delete (timer_);
    frameCount_ = 0;

    for (int i = 0; i < 50; gif.addFrame(images_[i++], 100)) {
    }
    QString filter = "GIF (*.gif)";
    QString filenameGif =
        QFileDialog::getSaveFileName(0, "Select where to save...", "", filter);
    gif.save(filenameGif);
  } else {
    images_[frameCount_++] =
        mainWindow_->ui->glwidget->grabFramebuffer().scaled(
            640, 480, Qt::IgnoreAspectRatio);
  }
}

void DownloadImageCommand::execute() {
  QImage image = mainWindow_->ui->glwidget->grabFramebuffer();
  QString filter = "JPEG (*.jpeg) ;; BMP (*.bmp)";
  QString path =
      QFileDialog::getSaveFileName(this, "Select where to save...", "", filter);
  if (!path.isNull()) image.save(path, NULL, 100);
}

}  // namespace s21
