#include "window.h"

#include <QDebug>
#include <QKeyEvent>
#include <QSurfaceFormat>

Window::Window(QSurfaceFormat::RenderableType renderableType,
        int majorVersion, int minorVersion) : QOpenGLWindow{}
{
    qDebug().noquote() << QString("Requested: OpenGL%1 %2.%3")
            .arg(renderableType == QSurfaceFormat::OpenGLES ? "ES" : "")
            .arg(majorVersion).arg(minorVersion);

    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setRenderableType(renderableType);
    format.setVersion(majorVersion, minorVersion);
    format.setSamples(4);
    setFormat(format);

    setTitle("Tutorial 01 - Empty Window");
    resize(640, 480);
}

Window::~Window()
{
}

void Window::initializeGL()
{
    initializeOpenGLFunctions();
    printOpenGlVersion();

    QColor clearColor{"#777"};
    glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
}

void Window::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::resizeGL(int w, int h)
{
    Q_UNUSED(w)
    Q_UNUSED(h)
}

void Window::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Escape)
        close();
}

void Window::printOpenGlVersion()
{
    GLint majorVersion, minorVersion;
    glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &minorVersion);

    qDebug().noquote() << QString("Loaded: OpenGL%1 %2.%3")
            .arg(context()->isOpenGLES() ? "ES" : "")
            .arg(majorVersion).arg(minorVersion);
}

void Window::printOpenGlExtraInfo()
{
    GLint max_vao;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_vao);
    qDebug() << "MAX VAO: " << max_vao;
}
