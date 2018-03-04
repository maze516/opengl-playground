#pragma once

#include <array>

class OpenGLVertex
{
public:
    OpenGLVertex(float x, float y, float z) {
        m_position[0] = x;
        m_position[1] = y;
        m_position[2] = z;
    }

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
