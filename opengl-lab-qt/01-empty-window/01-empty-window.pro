include(../opengl-wrapper/opengl-wrapper.pri)

TEMPLATE    =   app
TARGET      =   01-empty-window

DEFINES     +=  QT_OPENGL_DESKTOP
#DEFINES     +=  QT_OPENGL_ES2
#DEFINES     +=  QT_OPENGL_ES3

SOURCES     +=  main.cpp \
                window.cpp
HEADERS     +=  window.h
