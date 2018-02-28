#include "window.h"

#include <iostream>

void Window::initializeGL()
{
    OpenGLWindow::initializeGL();

    printOpenGlVersion();
    glClearColor(0.18f, 0.31f, 0.31f, 1.0f);
}

void Window::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::keyPressEvent(int key, int mods)
{
    (void) mods;

    if (key == GLFW_KEY_ESCAPE)
        close();
}

void Window::printOpenGlVersion()
{
    GLint majorVersion, minorVersion;
    glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &minorVersion);

    std::cout << "Loaded OpenGL " <<
            majorVersion << "." << minorVersion << std::endl;
}
