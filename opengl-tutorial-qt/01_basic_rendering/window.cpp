#include "window.h"

#include <QDebug>
#include <QKeyEvent>

#include <array>

#include "vertex.h"

static constexpr std::array<Vertex, 6> SHAPE {{
        Vertex {QVector3D {-0.5f, 0.5f, 0.0f}, QVector3D{0.988f, 0.890f, 0.541f}},
        Vertex {QVector3D {-1.0f,-0.5f, 0.0f}, QVector3D{0.988f, 0.890f, 0.541f}},
        Vertex {QVector3D { 0.0f,-0.5f, 0.0f}, QVector3D{0.988f, 0.890f, 0.541f}},
        Vertex {QVector3D { 0.5f,-0.5f, 0.0f}, QVector3D{0.953f, 0.506f, 0.506f}},
        Vertex {QVector3D { 0.0f, 0.5f, 0.0f}, QVector3D{0.953f, 0.506f, 0.506f}},
        Vertex {QVector3D { 1.0f, 0.5f, 0.0f}, QVector3D{0.953f, 0.506f, 0.506f}},
}};

Window::Window(QSurfaceFormat::RenderableType type,
        int majorVersion, int minorVersion) : QOpenGLWindow{},
    m_selectedTriangle {0}
{
    /*
     * Set OpenGL version information.
     * It has to be done before calling show()
     */
    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setRenderableType(type);
    format.setVersion(majorVersion, minorVersion);
    format.setSamples(4);
    setFormat(format);
}

Window::~Window()
{
    m_vertexArrayObject.destroy();
    m_vertexBufferObject.destroy();
    m_shaderProgram.removeAllShaders();
}

void Window::initializeGL()
{
    initializeOpenGLFunctions();
    printOpenGLVersion();

    QColor background {"#95e1d3"};
    glClearColor(
            static_cast<GLclampf>(background.redF()),
            static_cast<GLclampf>(background.greenF()),
            static_cast<GLclampf>(background.blueF()),
            static_cast<GLclampf>(background.alphaF()));

    // ** Create shaders and keep them bound until VAO is released ** //
    // Keep them bound to resolve uniforms if needed
    m_shaderProgram.create();
    m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader.vert");
    m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader.frag");
    if (m_shaderProgram.link())
        qDebug().noquote() << m_shaderProgram.log();
    m_shaderProgram.bind();

    // ** Create all objects ** //
    m_vertexBufferObject.create();
    m_vertexArrayObject.create();

    // ** Bind VAO ** //
    m_vertexArrayObject.bind();

    // ** Bind and configure VBO states ** //
    m_vertexBufferObject.bind();
    m_vertexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertexBufferObject.allocate(SHAPE.data(), sizeof(SHAPE));

    m_shaderProgram.enableAttributeArray(0);
    m_shaderProgram.setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(),
            Vertex::positionTupleSize(), Vertex::stride());
    m_shaderProgram.enableAttributeArray(1);
    m_shaderProgram.setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(),
            Vertex::colorTupleSize(), Vertex::stride());

    // ** Release all bound resources ** //
    m_vertexArrayObject.release();
    m_vertexBufferObject.release();
    m_shaderProgram.release();
}

void Window::resizeGL(int width, int height)
{
    Q_UNUSED(width)
    Q_UNUSED(height)
}

void Window::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    m_shaderProgram.bind();
    m_vertexArrayObject.bind();

    if (m_selectedTriangle & 0x01)
        glDrawArrays(GL_TRIANGLES, 0, 3);

    if (m_selectedTriangle & 0x02)
        glDrawArrays(GL_TRIANGLES, 3, 3);

    m_vertexArrayObject.release();
    m_shaderProgram.release();
}

void Window::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_T) {
        m_selectedTriangle = (m_selectedTriangle + 1) % 4;
        update();
    }
}

void Window::printOpenGLVersion()
{
    QString glType, glVersion, glProfile;

    glType = context()->isOpenGLES() ? "OpenGL ES" : "OpenGL";
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

    // Get profile information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
    switch (format().profile()) {
        CASE(NoProfile);
        CASE(CoreProfile);
        CASE(CompatibilityProfile);
    }

    qDebug().noquote().nospace() << "Loaded: " <<
            glType << " " << glVersion << " (" <<
            glProfile << ")";
}
