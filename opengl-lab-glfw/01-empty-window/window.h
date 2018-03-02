#pragma once

#include "openglwindow.h"

class Window : public OpenGLWindow {
public:
    using OpenGLWindow::OpenGLWindow;

protected:
    void initializeGL() override;
    void paintGL() override;

    void keyPressEvent(int key, int mods) override;
};
