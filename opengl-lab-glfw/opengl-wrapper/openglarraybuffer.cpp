#include "openglarraybuffer.h"

#include "logger.h"

#include <cassert>
#include <exception>

OpenGLArrayBuffer::~OpenGLArrayBuffer()
{
    if (!m_vbo)
        return;

    glDeleteBuffers(1, &m_vbo);
    DEBUG("OpenGLArrayBuffer: deleted VBO #" << m_vbo);
}

void OpenGLArrayBuffer::setUsage(Usage usage)
{
    assert(m_vbo);

    m_usage = usage;

    DEBUG("OpenGLArrayBuffer: initialized GL_ARRAY_BUFFER VBO #" << m_vbo <<
            " for " << toString(m_usage));
}

void OpenGLArrayBuffer::setBufferData(const void *data, long count)
{
    assert(m_vbo);

    glBufferData(GL_ARRAY_BUFFER, count, data, m_usage);
    DEBUG("OpenGLArrayBuffer: filled VBO #" << m_vbo <<
            " with " << count << " bytes");
}

void OpenGLArrayBuffer::bind()
{
    if (!m_vbo)
        create();

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    DEBUG("OpenGLArrayBuffer: bound VBO #" << m_vbo);
}

void OpenGLArrayBuffer::unbind()
{
    assert(m_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    DEBUG("OpenGLArrayBuffer: unbound VBO #" << m_vbo);
}

void OpenGLArrayBuffer::create()
{
    glGenBuffers(1, &m_vbo);
    DEBUG("OpenGLArrayBuffer: created VBO #" << m_vbo);
}

std::string OpenGLArrayBuffer::toString(Usage usage) const
{
    switch (usage) {
        case StaticDraw:
            return "StaticDraw";
    }
}
