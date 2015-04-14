
CONFIG = qt
CONFIG += c++11
QT     = core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = test2
INCLUDEPATH += . src
OBJECTS_DIR = obj
MOC_DIR = obj


HEADERS += src/mainwindow.h 

SOURCES += src/main.cpp src/mainwindow.cpp
