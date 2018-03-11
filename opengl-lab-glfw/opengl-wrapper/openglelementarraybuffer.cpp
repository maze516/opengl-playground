#include "openglelementarraybuffer.h"

#include "logger.h"

#include <cassert>
#include <exception>

OpenGLElementArrayBuffer::~OpenGLElementArrayBuffer()
{
    if (!m_ebo)
        return;

    glDeleteBuffers(1, &m_ebo);
    DEBUG("OpenGLElementArrayBuffer: deleted EBO #" << m_ebo);
}

void OpenGLElementArrayBuffer::setUsage(Usage usage)
{
    assert(m_ebo);

    m_usage = usage;

    DEBUG("OpenGLElementArrayBuffer: initialized GL_ELEMENT_ARRAY_BUFFER" <<
            " EBO #" << m_ebo << " for " << toString(m_usage));
}

void OpenGLElementArrayBuffer::setBufferData(const void *data, long count)
{
    assert(m_ebo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, data, m_usage);
    DEBUG("OpenGLElementArrayBuffer: filled EBO #" << m_ebo <<
            " with " << count << "bytes");
}

void OpenGLElementArrayBuffer::bind()
{
    if (!m_ebo)
        create();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    DEBUG("OpenGLElementArrayBuffer: bound EBO #" << m_ebo);
}

void OpenGLElementArrayBuffer::unbind()
{
    assert(m_ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    DEBUG("OpenGLElementArrayBuffer: unbound EBO #" << m_ebo);
}

void OpenGLElementArrayBuffer::create()
{
    glGenBuffers(1, &m_ebo);
    DEBUG("OpenGLElementArrayBuffer: created EBO #" << m_ebo);
}

std::string OpenGLElementArrayBuffer::toString(Usage usage) const
{
    switch (usage) {
        case StaticDraw:
            return "StaticDraw";
    }
}
