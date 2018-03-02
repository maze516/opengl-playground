#pragma once

#include <QOpenGLWindow>

#include <QElapsedTimer>
#include <QOpenGLFunctions>
#include <QSurfaceFormat>

class OpenGLWindow : public QOpenGLWindow, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OpenGLWindow();

    virtual ~OpenGLWindow();

protected:
    virtual void initializeGL() Q_DECL_OVERRIDE;
    virtual void paintGL() Q_DECL_OVERRIDE;
    virtual void resizeGL(int w, int h) Q_DECL_OVERRIDE;

    virtual void focusInEvent(QFocusEvent *ev) Q_DECL_OVERRIDE;
    virtual void focusOutEvent(QFocusEvent *ev) Q_DECL_OVERRIDE;

private:
    bool                m_pauseRendering;

    QElapsedTimer       m_fpsTimer;
    int                 m_frameCounter;
    double              m_fps;

    void printOpenGlVersion();

    void resetFpsCounter();
    void updateFpsCounter();
};
