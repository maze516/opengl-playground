#include "openglwindow.h"

#include <QDebug>
#include <QKeyEvent>
#include <QSurfaceFormat>

OpenGLWindow::OpenGLWindow() : QOpenGLWindow{},
    m_pauseRendering {false},
    m_frameCounter {0},
    m_fps {0.0}
{
    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setVersion(3, 3);
    format.setSamples(4);
    setFormat(format);

    qDebug().noquote() << QString("OpenGLWindow: requested OpenGL %1.%2")
            .arg(format.majorVersion()).arg(format.minorVersion());
}

OpenGLWindow::~OpenGLWindow()
{
}

void OpenGLWindow::initializeGL()
{
    initializeOpenGLFunctions();
    printOpenGlVersion();

    resetFpsCounter();
}

void OpenGLWindow::paintGL()
{
    if (!m_pauseRendering) {
        // Update FPS counter (every 5 seconds)
        updateFpsCounter();

        // Trigger an update on next vsync continuously
        update();
    } else {
        resetFpsCounter();
    }
}

void OpenGLWindow::resizeGL(int w, int h)
{
    Q_UNUSED(w)
    Q_UNUSED(h)

    qDebug().noquote() << QString("OpenGLWindow: resize to %1x%2")
            .arg(w).arg(h);
    glViewport(0, 0, w, h);
}

void OpenGLWindow::focusInEvent(QFocusEvent *ev)
{
    Q_UNUSED(ev);
    qDebug().noquote() << "OpenGLWindow: focus in event";
    m_pauseRendering = false;

    // Trigger a new update on next vsync
    resetFpsCounter();
    update();
}

void OpenGLWindow::focusOutEvent(QFocusEvent *ev)
{
    Q_UNUSED(ev);
    qDebug().noquote() << "OpenGLWindow: focus out event";
    m_pauseRendering = true;
}

void OpenGLWindow::printOpenGlVersion()
{
    GLint majorVersion, minorVersion;
    glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &minorVersion);

    qDebug().noquote() << QString("OpenGLWindow: loaded OpenGL %1.%2")
            .arg(majorVersion).arg(minorVersion);
}

void OpenGLWindow::resetFpsCounter()
{
    m_frameCounter = 0;
    m_fpsTimer.start();
}

void OpenGLWindow::updateFpsCounter()
{
    m_frameCounter++;
    auto elapsedTime = m_fpsTimer.elapsed();

    if (elapsedTime > 5000.0) {
        m_fps = m_frameCounter * 1000.0 / elapsedTime;
        qDebug().noquote() <<
                QString("OpenGLWindow: %1 frames in %2 s = %3 FPS")
                        .arg(m_frameCounter)
                        .arg(elapsedTime / 1000.0, 0, 'f', 3)
                        .arg(m_fps, 0, 'f', 3);
        resetFpsCounter();
    }
}
