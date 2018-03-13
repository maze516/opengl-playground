#include "window.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>

#include "logger.h"
#include "openglcolorvertex.h"

static constexpr std::array<OpenGLColorVertex, 3> SHAPE {{
        OpenGLColorVertex { 0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f},
        OpenGLColorVertex {-0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f},
        OpenGLColorVertex { 0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f},
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
            SHAPE.size() * OpenGLColorVertex::stride());

    m_vertexArray.setVertexAttributeBuffer(0, OpenGLColorVertex::stride(),
            OpenGLColorVertex::positionOffset());
    m_vertexArray.enableVertexAttributeArray(0);
    m_vertexArray.setVertexAttributeBuffer(1, OpenGLColorVertex::stride(),
            OpenGLColorVertex::colorOffset());
    m_vertexArray.enableVertexAttributeArray(1);

    m_vertexArray.unbind();
    m_shape.unbind();
}

void Window::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    m_shaderProgram.use();
    m_vertexArray.bind();

    double time = glfwGetTime();
    m_shaderProgram.setUniform("uniformColor", m_uniformColor);
    float r = 0.75f + static_cast<float>(sin(time / 3.77) * 0.25);
    float g = 0.75f + static_cast<float>(sin(time / 2.04) * 0.25);
    float b = 0.75f + static_cast<float>(sin(time / 1.23) * 0.25);
    m_shaderProgram.setUniform("triangleColor", r, g, b);
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

        case GLFW_KEY_SPACE:
            m_uniformColor = !m_uniformColor;
            break;
    }
}
