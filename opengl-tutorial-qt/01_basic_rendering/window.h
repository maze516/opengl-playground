#pragma once

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QSurfaceFormat>

class QKeyEvent;

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

    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

private:
    QOpenGLShaderProgram        m_shaderProgram;
    QOpenGLBuffer               m_vertexBufferObject;
    QOpenGLVertexArrayObject    m_vertexArrayObject;
    int                         m_selectedTriangle;

    void printOpenGLVersion();
};
