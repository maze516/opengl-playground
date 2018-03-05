#include "openglwindow.h"

#include "logger.h"
#include "simpletimer.h"

#include <exception>
#include <iomanip>

OpenGLWindow::OpenGLWindow(int width, int height, const std::string &title) :
    m_gladInitialized {false},
    m_pauseRendering {false},
    m_frameCounter {0},
    m_fps {0.0}
{
    // Initialize GLFW
    if (!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW!");

    // Version 3.3.0 or higher is required on macOS
    DEBUG("OpenGLWindow: initialized GLFW v" << glfwGetVersionString());

    // Init OpenGL settings
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_SAMPLES, 16);

    // Create window
    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    glfwSetWindowUserPointer(m_window, this);
    if (!m_window) {
        glfwTerminate();
        throw std::runtime_error("OpenGLWindow: failed to create GLFW window!");
    }
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);

    // Set the required callback functions
    glfwSetKeyCallback(m_window, keyCallback);
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
    glfwSetWindowFocusCallback(m_window, windowFocusCallback);
    glfwSetErrorCallback(errorCallback);
}

OpenGLWindow::~OpenGLWindow()
{
    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    DEBUG("OpenGLWindow: cleanup completed");
}

int OpenGLWindow::exec()
{
    // Initialize OpenGL
    initializeGL();
    int width, height;
    glfwGetWindowSize(m_window, &width, &height);
    resizeGL(width, height);

    resetFpsCounter();

    // Graphics loop
    while (!glfwWindowShouldClose(m_window)) {
        if (!m_pauseRendering) {
            // Update FPS counter (every 5 seconds)
            updateFpsCounter();

            // Paint OpenGL stuff
            paintGL();

            // Swap the screen buffers
            glfwSwapBuffers(m_window);

            /*
             * Check for events (key pressed, mouse moved etc.)
             * Should be done after swap buffer?  If done before, black screen
             * is shown at startup...
             */
            glfwPollEvents();
        } else {
            glfwWaitEvents();
            resetFpsCounter();
        }
    }

    return 0;
}

void OpenGLWindow::close()
{
    assert(m_window);

    glfwSetWindowShouldClose(m_window, GL_TRUE);
}

bool OpenGLWindow::glInitialized() const
{
    return m_gladInitialized;
}

void OpenGLWindow::initializeGL()
{
    assert(m_window);

    // Initialize GLAD
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD!");
    }

    m_gladInitialized = true;
    printOpenGlVersion();
}

void OpenGLWindow::resizeGL(int width, int height)
{
    DEBUG("OpenGLWindow: resize to " << width << "x" << height);
    glViewport(0, 0, width, height);
}

void OpenGLWindow::keyPressEvent(int key, int mods)
{
    (void) key;
    (void) mods;
}

void OpenGLWindow::keyReleaseEvent(int key, int mods)
{
    (void) key;
    (void) mods;
}

void OpenGLWindow::focusInEvent()
{
    m_pauseRendering = false;
}

void OpenGLWindow::focusOutEvent()
{
    m_pauseRendering = true;
}

void OpenGLWindow::keyCallback(GLFWwindow *window, int key,
        int scancode, int action, int mods)
{
    (void) scancode;

    auto w = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(window));
    if (action == GLFW_PRESS) {
        DEBUG("OpenGLWindow: pressed key " << key);
        w->keyPressEvent(key, mods);
    } else if (action == GLFW_RELEASE) {
        DEBUG("OpenGLWindow: released key " << key);
        w->keyReleaseEvent(key, mods);
    }
}

void OpenGLWindow::framebufferSizeCallback(GLFWwindow *window,
        int width, int height)
{
    auto w = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(window));
    w->resizeGL(width, height);
}

void OpenGLWindow::errorCallback(int code, const char *description)
{
    std::cerr << "OpenGLWindow: error " <<
            code << " (" << description << ")" << std::endl;
}

void OpenGLWindow::windowFocusCallback(GLFWwindow *window, int focused)
{
    /*
     * Rendering is paused while window is not focused.  Maybe it's enough
     * to pause rendering when iconified, but on macOS it doesn't work.
     */
    auto w = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(window));
    if (focused == GLFW_TRUE) {
        DEBUG("OpenGLWindow: focus in event");
        w->focusInEvent();
    } else {
        DEBUG("OpenGLWindow: focus out event");
        w->focusOutEvent();
    }
}

void OpenGLWindow::printOpenGlVersion()
{
    GLint majorVersion, minorVersion;
    glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &minorVersion);

    DEBUG("OpenGLWindow: loaded OpenGL " <<
            majorVersion << "." << minorVersion);
}

void OpenGLWindow::resetFpsCounter()
{
    m_frameCounter = 0;
    m_fpsTimer.reset();
}

void OpenGLWindow::updateFpsCounter()
{
    m_frameCounter++;
    auto elapsedTime = m_fpsTimer.elapsed();

    if (elapsedTime > 5000.0) {
        m_fps = m_frameCounter * 1000 / elapsedTime;
        DEBUG(std::fixed << std::setprecision(3) <<
                "OpenGLWindow: " << m_frameCounter << " frames in " <<
                elapsedTime / 1000.0 << " s = " <<
                m_fps << "FPS" <<
                std::defaultfloat);
        resetFpsCounter();
    }
}
