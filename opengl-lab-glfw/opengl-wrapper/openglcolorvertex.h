#pragma once

#include <array>

class OpenGLColorVertex
{
public:
    constexpr OpenGLColorVertex(float x, float y, float z,
            float r, float g, float b) :
        m_position {{x, y, z}}, m_color {{r, g, b}} { }

    static constexpr int positionOffset() {
        return offsetof(OpenGLColorVertex, m_position);
    }

    static constexpr int colorOffset() {
        return offsetof(OpenGLColorVertex, m_color);
    }

    static constexpr int stride() {
        return sizeof(OpenGLColorVertex);
    }

    constexpr float x() const {
        return m_position[0];
    }

    constexpr float y() const {
        return m_position[1];
    }

    constexpr float z() const {
        return m_position[2];
    }

    constexpr float r() const {
        return m_color[0];
    }

    constexpr float g() const {
        return m_color[1];
    }

    constexpr float b() const {
        return m_color[2];
    }

private:
    static constexpr size_t         VERTEX_SIZE {3};
    std::array<float, VERTEX_SIZE>  m_position;
    static constexpr size_t         COLOR_SIZE {3};
    std::array<float, COLOR_SIZE>   m_color;
};
