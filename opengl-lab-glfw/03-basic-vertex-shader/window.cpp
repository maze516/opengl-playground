#include "window.h"

#include <algorithm>
#include <array>
#include <iostream>

#include "logger.h"
#include "openglvertex.h"

static constexpr std::array<OpenGLVertex, 3> SHAPE {{
        OpenGLVertex {-0.5f, -0.5f,  0.0f},
        OpenGLVertex { 0.5f, -0.5f,  0.0f},
        OpenGLVertex { 0.5f,  0.5f,  0.0f},
}};

void Window::initializeGL()
{
    OpenGLWindow::initializeGL();
    glClearColor(0.96f, 0.64f, 0.38f, 1.0f);

    m_shaderProgram.addShader(OpenGLShaderProgram::Vertex, "shader.vsh");
    m_shaderProgram.addShader(OpenGLShaderProgram::Fragment, "shader.fsh");
    m_shaderProgram.link();

    m_vertexArray.bind();
    m_shape.bind();

    m_shape.setBufferData(SHAPE.data(),
            SHAPE.size() * OpenGLVertex::stride());

    m_vertexArray.setVertexAttributeBuffer(0, OpenGLVertex::stride(),
            OpenGLVertex::positionOffset());
    m_vertexArray.enableVertexAttributeArray(0);

    m_vertexArray.unbind();
    m_shape.unbind();
}

void Window::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    m_shaderProgram.use();
    m_vertexArray.bind();
    m_shaderProgram.setUniform("flipHorizontal", m_flipHorizontal);
    m_shaderProgram.setUniform("flipVertical", m_flipVertical);
    m_shaderProgram.setUniform("offsetHorizontal", m_offsetHorizontal);
    m_shaderProgram.setUniform("offsetVertical", m_offsetVertical);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    m_vertexArray.unbind();
}

void Window::keyPressEvent(int key, int mods)
{
    (void) mods;

    if (!glInitialized())
        return;

    switch (key) {
        default:
            break;

        case GLFW_KEY_ESCAPE:
            close();
            break;

        case GLFW_KEY_H:
            m_flipHorizontal = !m_flipHorizontal;
            break;

        case GLFW_KEY_V:
            m_flipVertical = !m_flipVertical;
            break;

        case GLFW_KEY_SPACE:
            m_offsetVertical = 0.0f;
            m_offsetHorizontal = 0.0f;
            PRINT_VALUE(m_offsetVertical);
            PRINT_VALUE(m_offsetHorizontal);
            break;

        case GLFW_KEY_UP:
            m_offsetVertical = 1.0f - std::max_element(
                    SHAPE.cbegin(), SHAPE.cend(),
                    [](const OpenGLVertex &v1, const OpenGLVertex &v2) {
                        return (v1.y() < v2.y());
                    })->y();
            m_offsetHorizontal = 0.0f;
            PRINT_VALUE(m_offsetVertical);
            PRINT_VALUE(m_offsetHorizontal);
            break;

        case GLFW_KEY_LEFT:
            m_offsetVertical = 0.0f;
            m_offsetHorizontal = -1.0f - std::min_element(
                    SHAPE.cbegin(), SHAPE.cend(),
                    [](const OpenGLVertex &v1, const OpenGLVertex &v2) {
                        return (v1.x() < v2.x());
                    })->x();
            PRINT_VALUE(m_offsetVertical);
            PRINT_VALUE(m_offsetHorizontal);
            break;

        case GLFW_KEY_DOWN:
            m_offsetVertical = -1.0f - std::min_element(
                    SHAPE.cbegin(), SHAPE.cend(),
                    [](const OpenGLVertex &v1, const OpenGLVertex &v2) {
                        return (v1.y() < v2.y());
                    })->y();
            m_offsetHorizontal = 0.0f;
            PRINT_VALUE(m_offsetVertical);
            PRINT_VALUE(m_offsetHorizontal);
            break;

        case GLFW_KEY_RIGHT:
            m_offsetVertical = 0.0f;
            m_offsetHorizontal = 1.0f - std::max_element(
                    SHAPE.cbegin(), SHAPE.cend(),
                    [](const OpenGLVertex &v1, const OpenGLVertex &v2) {
                        return (v1.x() < v2.x());
                    })->x();
            PRINT_VALUE(m_offsetVertical);
            PRINT_VALUE(m_offsetHorizontal);
            break;
    }
}
