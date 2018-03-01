#pragma once

#include "openglwindow.h"

class Window : public OpenGLWindow {
protected:
    void initializeGL() override;
    void paintGL() override;

    void keyPressEvent(int key, int mods) override;
};
