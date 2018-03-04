#include "window.h"

#include <iostream>
#include <array>
#include <openglvertex.h>

static const std::array<OpenGLVertex, 3> VERTICES {{
    OpenGLVertex {-0.5f, -0.5f,  0.0f},
    OpenGLVertex { 0.5f, -0.5f,  0.0f},
    OpenGLVertex { 0.0f,  0.5f,  0.0f}
}};

void Window::initializeGL()
{
    OpenGLWindow::initializeGL();
    glClearColor(0.18f, 0.31f, 0.31f, 1.0f);

    m_triangle.bind();
    m_triangle.setBufferData(VERTICES.data(),
            VERTICES.size() * OpenGLVertex::stride());

    m_shaderProgram.addShader(OpenGLShaderProgram::Vertex, "shader.vsh");
    m_shaderProgram.addShader(OpenGLShaderProgram::Fragment, "shader.fsh");
    m_shaderProgram.link();

    m_vertexArray.bind();
    m_vertexArray.setVertexAttributeBuffer(0, OpenGLVertex::stride(),
            OpenGLVertex::positionOffset());
    m_vertexArray.enableVertexAttributeArray(0);
    m_vertexArray.unbind();

    m_triangle.unbind();
}

void Window::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    m_shaderProgram.use();
    m_vertexArray.bind();
    glPolygonMode(GL_FRONT_AND_BACK, m_wireframe ? GL_LINE : GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, VERTICES.size());
    m_vertexArray.unbind();
}

void Window::keyPressEvent(int key, int mods)
{
    (void) mods;

    if (key == GLFW_KEY_ESCAPE)
        close();
    else if (key == GLFW_KEY_W)
        m_wireframe = !m_wireframe;
}
