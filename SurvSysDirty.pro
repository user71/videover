#-------------------------------------------------
#
# Project created by QtCreator 2017-06-10T23:50:56
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = SurvSysDirty
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp \
    VideoReceiver.cpp \
    CameraInteractor.cpp \
    FlowAnalyzer.cpp \
    LogService.cpp \
    Camera.cpp

HEADERS += \
    VideoReceiver.h \
    CameraInteractor.h \
    FlowAnalyzer.h \
    LogService.h \
    common.h \
    Camera.h

unix:!macx: LIBS += -L/opt/opencv-2.4.4/lib/ -lopencv_core -lopencv_video -lopencv_contrib -lopencv_imgproc -lopencv_highgui -lopencv_objdetect

INCLUDEPATH += /opt/opencv-2.4.4/include
DEPENDPATH += /opt/opencv-2.4.4/include

#unix:!macx: LIBS += -L$$PWD/../../../opt/opencv-2.4.4/lib/ -lopencv_core -lopencv_video -lopencv_contrib -lopencv_imgproc -lopencv_highgui -lopencv_objdetect

#INCLUDEPATH += $$PWD/../../../opt/opencv-2.4.4/include
#DEPENDPATH += $$PWD/../../../opt/opencv-2.4.4/include


