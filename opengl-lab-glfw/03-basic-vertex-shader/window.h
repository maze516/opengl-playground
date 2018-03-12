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
    OpenGLVertexArray           m_vertexArray;
    OpenGLArrayBuffer           m_shape;
    bool                        m_flipVertical {false};
    bool                        m_flipHorizontal {false};
    float                       m_offsetVertical {0.0f};
    float                       m_offsetHorizontal {0.0f};
};
