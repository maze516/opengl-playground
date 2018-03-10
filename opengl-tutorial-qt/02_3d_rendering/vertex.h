#pragma once

#include <QVector3D>

class Vertex
{
public:
    // ** Constructors ** //
    Q_DECL_CONSTEXPR Vertex() :
        Vertex {{}} {}

    Q_DECL_CONSTEXPR Vertex(const QVector3D &position) :
        Vertex {position, QVector3D {1.0f, 1.0f, 1.0f}} {}

    Q_DECL_CONSTEXPR Vertex(const QVector3D &position, const QVector3D &color) :
        m_position {position},
        m_color {color} {}

    // ** Accessors - Mutators ** //
    Q_DECL_CONSTEXPR const QVector3D &position() const {
        return m_position;
    }

    void setPosition(const QVector3D &position) {
        m_position = position;
    }

    Q_DECL_CONSTEXPR const QVector3D &color() const {
        return m_color;
    }

    void setColor(const QVector3D &color) {
        m_color = color;
    }

    // ** OpenGL helpers ** //
    static Q_DECL_CONSTEXPR int positionTupleSize() {
        return 3;
    }

    static Q_DECL_CONSTEXPR int colorTupleSize() {
        return 3;
    }

    static Q_DECL_CONSTEXPR int positionOffset() {
        return offsetof(Vertex, m_position);
    }

    static Q_DECL_CONSTEXPR int colorOffset() {
        return offsetof(Vertex, m_color);
    }

    static Q_DECL_CONSTEXPR int stride() {
        return sizeof(Vertex);
    }

private:
    QVector3D       m_position;
    QVector3D       m_color;
};
