#include "window.h"

#include <array>
#include <iostream>

#include "openglvertex.h"

static constexpr std::array<OpenGLVertex, 6> SHAPE {{
        OpenGLVertex {-0.75f, -0.50f,  0.00f},
        OpenGLVertex { 0.25f, -0.50f,  0.00f},
        OpenGLVertex {-0.25f,  0.50f,  0.00f},
        OpenGLVertex {-0.25f,  0.50f,  0.00f},
        OpenGLVertex { 0.75f,  0.50f,  0.00f},
        OpenGLVertex { 0.25f, -0.50f,  0.00f},
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
    if (m_selectedTriangle & 0x01)
        glDrawArrays(GL_TRIANGLES, 0, 3);
    if (m_selectedTriangle & 0x02)
        glDrawArrays(GL_TRIANGLES, 3, 6);
    m_vertexArray.unbind();
}

void Window::keyPressEvent(int key, int mods)
{
    (void) mods;

    if (!glInitialized())
        return;

    if (key == GLFW_KEY_ESCAPE) {
        close();
    } else if (key == GLFW_KEY_W) {
        m_wireframe = !m_wireframe;
        glPolygonMode(GL_FRONT_AND_BACK, m_wireframe ? GL_LINE : GL_FILL);
    } else if (key == GLFW_KEY_T) {
        m_selectedTriangle = (m_selectedTriangle + 1) % 4;
    }
}
