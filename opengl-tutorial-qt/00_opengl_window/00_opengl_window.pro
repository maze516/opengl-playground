QT          +=  core gui

CONFIG      +=  c++11
#CONFIG      +=  console
CONFIG      -=  app_bundle

TEMPLATE    =   app

SOURCES     +=  \
                window.cpp \
                main.cpp

HEADERS     +=  \
                window.h
