#pragma once

#include <QVector3D>
#include <QDataStream>
#include <QDebug>

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

    friend QDataStream &operator<<(QDataStream &out, const Vertex &vertex);
    friend QDataStream &operator>>(QDataStream &in, Vertex &vertex);
};

// ** Qt streams ** //
#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug stream, const Vertex &vertex) {
    QVector3D p = vertex.position();
    QVector3D c = vertex.color();
    stream.noquote().nospace() <<
            QString("{x: %1, y: %2, z: %3}, ").arg(p.x()).arg(p.y()).arg(p.z()) <<
            QString("{r: %1, g: %2, b: %3}").arg(c.x()).arg(c.y()).arg(c.z());
    return stream;
}
#endif

#ifndef QT_NO_DATASTREAM
QDataStream &operator<<(QDataStream &out, const Vertex &vertex)
{
    out << vertex.m_position;
    out << vertex.m_color;
    return out;
}

QDataStream &operator>>(QDataStream &in, Vertex &vertex)
{
    in >> vertex.m_position;
    in >> vertex.m_color;
    return in;
}
#endif

// Note: Q_MOVABLE_TYPE means it can be memcpy'd.
Q_DECLARE_TYPEINFO(Vertex, Q_MOVABLE_TYPE);
