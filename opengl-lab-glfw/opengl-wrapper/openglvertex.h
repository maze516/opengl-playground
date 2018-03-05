#pragma once

#include <array>

class OpenGLVertex
{
public:
    constexpr OpenGLVertex(float x, float y, float z) :
        m_position {{x, y, z}} { }

    static constexpr int positionOffset() {
        return offsetof(OpenGLVertex, m_position);
    }

    static constexpr int stride() {
        return sizeof(OpenGLVertex);
    }

private:
    static constexpr size_t         VERTEX_SIZE {3};
    std::array<float, VERTEX_SIZE>  m_position;
};
