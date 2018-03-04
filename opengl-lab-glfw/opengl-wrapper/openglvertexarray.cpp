#include "openglvertexarray.h"

#include "logger.h"

#include <cassert>
#include <exception>

OpenGLVertexArray::~OpenGLVertexArray()
{
    if (!m_vao)
        return;

    glDeleteVertexArrays(1, &m_vao);
    DEBUG("OpenGLVertexArray: deleted VAO #" << m_vao);
}

void OpenGLVertexArray::bind()
{
    if (!m_vao)
        create();

    glBindVertexArray(m_vao);
}

void OpenGLVertexArray::unbind()
{
    assert(m_vao);

    glBindVertexArray(0);
}

void OpenGLVertexArray::setVertexAttributeBuffer(unsigned int attribute,
        int stride, int offset)
{
    assert(m_vao);
    glVertexAttribPointer(attribute, 3, GL_FLOAT, GL_FALSE, stride,
            reinterpret_cast<void *>(offset));
    DEBUG("OpenGLVertexArray: set attribute #" << attribute <<
          " for VAO #" << m_vao <<
          " with stride: " << stride << ", offset: " << offset);
}

void OpenGLVertexArray::enableVertexAttributeArray(unsigned int attribute)
{
    assert(m_vao);
    glEnableVertexAttribArray(attribute);
    DEBUG("OpenGLVertexArray: enabled attribute #" << attribute <<
          " for VAO #" << m_vao);
}

void OpenGLVertexArray::create()
{
    glGenVertexArrays(1, &m_vao);
    DEBUG("OpenGLVertexArray: created VAO #" << m_vao);
}
