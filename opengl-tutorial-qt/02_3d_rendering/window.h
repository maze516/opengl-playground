#pragma once

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QSurfaceFormat>
#include <QMatrix4x4>

class QMouseEvent;

class Window : public QOpenGLWindow,
               protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Window() : Window{QSurfaceFormat::OpenGL, 3, 3} {}
    Window(QSurfaceFormat::RenderableType type,
           int majorVersion, int minorVersion);

    virtual ~Window();

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QOpenGLShaderProgram        m_shaderProgram;
    QOpenGLBuffer               m_vertexBufferObject;
    QOpenGLBuffer               m_elementBufferObject;
    QOpenGLVertexArrayObject    m_vertexArrayObject;

    QMatrix4x4                  m_modelMatrix;
    QMatrix4x4                  m_viewMatrix;
    QMatrix4x4                  m_projectionMatrix;

    size_t                      m_selectedRotation;

    void printOpenGLVersion();
};
