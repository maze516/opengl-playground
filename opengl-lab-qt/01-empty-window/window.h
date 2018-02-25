#pragma once

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QSurfaceFormat>

class Window : public QOpenGLWindow, protected QOpenGLFunctions {
    Q_OBJECT

public:
    Window() : Window(QSurfaceFormat::OpenGLES, 2, 0) {}
    Window(QSurfaceFormat::RenderableType renderableType, int majorVersion, int minorVersion);
    virtual ~Window();

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;

    void keyPressEvent(QKeyEvent *ev) Q_DECL_OVERRIDE;

private:
    void printOpenGlVersion();
    void printOpenGlExtraInfo();
};
