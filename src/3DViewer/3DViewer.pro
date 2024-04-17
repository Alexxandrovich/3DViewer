QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(QtGifImage/src/gifimage/qtgifimage.pri)

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/controller.cc \
    model/s21_3d_viewer.cc \
    view/gl_class.cc \
    view/main.cc \
    view/mainwindow.cc \
    view/strategy_options.cc \
    view/command.cc

HEADERS += \
    controller/controller.h \
    model/s21_3d_viewer.h \
    view/gl_class.h \
    view/mainwindow.h \
    view/strategy_options.h \
    view/command.h

FORMS += \
    view/mainwindow.ui

INCLUDEPATH += model/ \
    view/ \
    controller/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
