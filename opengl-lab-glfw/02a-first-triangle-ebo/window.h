#pragma once

#include "openglwindow.h"
#include "openglarraybuffer.h"
#include "openglelementarraybuffer.h"
#include "openglshaderprogram.h"
#include "openglvertexarray.h"

#include <memory>

class Window : public OpenGLWindow {
public:
    using OpenGLWindow::OpenGLWindow;

protected:
    void initializeGL() override;
    void paintGL() override;

    void keyPressEvent(int key, int mods) override;

private:
    OpenGLShaderProgram         m_shaderProgram;
    OpenGLShaderProgram         m_shaderProgram2;
    OpenGLVertexArray           m_vertexArray;
    OpenGLArrayBuffer           m_shape;
    OpenGLElementArrayBuffer    m_elementArrayBuffer;
    bool                        m_wireframe {false};
    int                         m_selectedTriangle {0};
};
