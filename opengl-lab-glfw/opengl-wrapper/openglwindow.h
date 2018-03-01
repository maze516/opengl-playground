#pragma once

#include <string>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#include "glad/glad.h"
#pragma clang diagnostic pop
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "simpletimer.h"

class OpenGLWindow {
public:
    OpenGLWindow() : OpenGLWindow(640, 480, "OpenGLWindow") {}
    OpenGLWindow(int width, int height, const std::string &title);

    virtual ~OpenGLWindow();

    int exec();

    void close();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int width, int height);
    virtual void paintGL() = 0;

    virtual void keyPressEvent(int key, int mods);
    virtual void keyReleaseEvent(int key, int mods);
    virtual void focusInEvent();
    virtual void focusOutEvent();

private:
    GLFWwindow          *m_window;
    bool                m_pauseRendering;

    SimpleTimer         m_fpsTimer;
    int                 m_frameCounter;
    double              m_fps;

    static void keyCallback(GLFWwindow *window,
            int key, int scancode, int action, int mode);
    static void framebufferSizeCallback(GLFWwindow *window,
            int width, int height);
    static void errorCallback(int code, const char *description);
    static void windowFocusCallback(GLFWwindow *window, int focused);

    void printOpenGlVersion();

    void resetFpsCounter();
    void updateFpsCounter();
};
