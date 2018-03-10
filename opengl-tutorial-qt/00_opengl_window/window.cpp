#include "window.h"

#include <QDebug>

Window::Window(QSurfaceFormat::RenderableType type,
        int majorVersion, int minorVersion) : QOpenGLWindow{}
{
    /*
     * Set OpenGL version information.
     * It has to be done before calling show()
     */
    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setRenderableType(type);
    format.setVersion(majorVersion, minorVersion);
    format.setSamples(4);
    setFormat(format);
}

void Window::initializeGL()
{
    initializeOpenGLFunctions();
    printOpenGLVersion();

    QColor background {"#95e1d3"};
    glClearColor(
            static_cast<GLclampf>(background.redF()),
            static_cast<GLclampf>(background.greenF()),
            static_cast<GLclampf>(background.blueF()),
            static_cast<GLclampf>(background.alphaF()));
}

void Window::resizeGL(int width, int height)
{
    Q_UNUSED(width)
    Q_UNUSED(height)
}

void Window::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::printOpenGLVersion()
{
    QString glType, glVersion, glProfile;

    glType = context()->isOpenGLES() ? "OpenGL ES" : "OpenGL";
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

    // Get profile information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
    switch (format().profile()) {
        CASE(NoProfile);
        CASE(CoreProfile);
        CASE(CompatibilityProfile);
    }

    qDebug().noquote().nospace() << "Loaded: " <<
            glType << " " << glVersion << " (" <<
            glProfile << ")";
}
