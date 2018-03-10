#pragma once

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QSurfaceFormat>

class Window : public QOpenGLWindow,
               protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Window() : Window{QSurfaceFormat::OpenGL, 3, 3} {}
    Window(QSurfaceFormat::RenderableType type,
           int majorVersion, int minorVersion);

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

private:
    void printOpenGLVersion();
};
