#pragma once

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#include "glad/glad.h"
#pragma clang diagnostic pop

#include <string>

class OpenGLVertexArray {
public:
    enum Usage : GLenum {
        StaticDraw = GL_STATIC_DRAW,
    };

    virtual ~OpenGLVertexArray();

    void bind();
    void unbind();

    void setVertexAttributeBuffer(unsigned int attribute,
            int stride, int offset);
    void enableVertexAttributeArray(unsigned int attribute);

private:
    GLuint              m_vao {0};

    void create();
};
