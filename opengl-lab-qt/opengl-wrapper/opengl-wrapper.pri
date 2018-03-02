QT          +=  core gui
CONFIG      +=  c++14

#QMAKE_CXXFLAGS += -isystem /opt/Qt/5.9.1/clang_64/lib/QtCore.framework/Headers
#QMAKE_CXXFLAGS += -isystem /opt/Qt/5.9.1/clang_64/lib/QtGui.framework/Headers
#QMAKE_CXXFLAGS += -Weverything -Wno-c++98-compat
DEFINES     +=  QT_DEPRECATED_WARNINGS

SOURCES     +=  $$PWD/openglwindow.cpp
HEADERS     +=  $$PWD/openglwindow.h

INCLUDEPATH +=  $$PWD
