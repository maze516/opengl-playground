#pragma once

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#include "glad/glad.h"
#pragma clang diagnostic pop

#include <string>

class OpenGLArrayBuffer {
public:
    enum Usage : GLenum {
        StaticDraw = GL_STATIC_DRAW,
    };

    OpenGLArrayBuffer() = default;
    OpenGLArrayBuffer(OpenGLArrayBuffer const &x) = delete;
    void operator=(OpenGLArrayBuffer const &x) = delete;

    virtual ~OpenGLArrayBuffer();

    void setUsage(Usage usage);

    void setBufferData(const void *data, long count);

    void bind();
    void unbind();

private:

    GLuint              m_vbo {0};
    Usage               m_usage {StaticDraw};

    void create();

    std::string toString(Usage usage) const;
};
