#pragma once

#include "openglwindow.h"
#include "openglarraybuffer.h"
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
    OpenGLShaderProgram m_shaderProgram;
    OpenGLVertexArray   m_vertexArray;
    OpenGLArrayBuffer   m_shape;
    int                 m_shapeVertexCount;
    bool                m_wireframe {false};
};
