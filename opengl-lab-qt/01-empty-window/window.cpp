#include "window.h"

#include <QDebug>
#include <QKeyEvent>

Window::Window() : OpenGLWindow{}
{
    setTitle("01 - Empty Window");
    resize(640, 480);
}

void Window::initializeGL()
{
    OpenGLWindow::initializeGL();
    printOpenGlExtraInfo();

    QColor clearColor{"#2f4f4f"};
    glClearColor(clearColor.redF(), clearColor.greenF(),
            clearColor.blueF(), clearColor.alphaF());
}

void Window::paintGL()
{
    OpenGLWindow::paintGL();

    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Escape)
        close();
}

void Window::printOpenGlExtraInfo()
{
    GLint max_vao;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_vao);
    qDebug() << "MAX VAO: " << max_vao;
}
