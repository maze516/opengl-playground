#pragma once

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#include "glad/glad.h"
#pragma clang diagnostic pop

#include <string>

class OpenGLElementArrayBuffer {
public:
    enum Usage : GLenum {
        StaticDraw = GL_STATIC_DRAW,
    };

    OpenGLElementArrayBuffer() = default;
    OpenGLElementArrayBuffer(OpenGLElementArrayBuffer const &x) = delete;
    void operator=(OpenGLElementArrayBuffer const &x) = delete;

    virtual ~OpenGLElementArrayBuffer();

    void setUsage(Usage usage);

    void setBufferData(const void *data, long count);

    void bind();
    void unbind();

private:
    GLuint              m_ebo {0};
    Usage               m_usage {StaticDraw};

    void create();

    std::string toString(Usage usage) const;
};
