#include "window.h"

#include <iostream>

void Window::initializeGL()
{
    OpenGLWindow::initializeGL();
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
