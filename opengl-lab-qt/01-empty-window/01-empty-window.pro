QT          +=  core gui
CONFIG      +=  c++14

TEMPLATE    =   app
TARGET      =   01_empty_window_qt

DEFINES     +=  QT_DEPRECATED_WARNINGS
DEFINES     +=  QT_OPENGL_DESKTOP

SOURCES     +=  main.cpp \
                window.cpp
HEADERS     +=  window.h
