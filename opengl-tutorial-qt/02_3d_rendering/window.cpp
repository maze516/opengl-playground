#include "window.h"

#include <QDebug>
#include <QMouseEvent>

#include <array>

#include "vertex.h"

static constexpr std::array<Vertex, 8> VERTEX {{
        /*FTR*/ Vertex {QVector3D { 0.5f, 0.5f, 0.5f}, QVector3D{0.988f, 0.890f, 0.541f}},
        /*FTL*/ Vertex {QVector3D {-0.5f, 0.5f, 0.5f}, QVector3D{0.988f, 0.890f, 0.541f}},
        /*FBL*/ Vertex {QVector3D {-0.5f,-0.5f, 0.5f}, QVector3D{0.953f, 0.506f, 0.506f}},
        /*FBR*/ Vertex {QVector3D { 0.5f,-0.5f, 0.5f}, QVector3D{0.953f, 0.506f, 0.506f}},
        /*BTR*/ Vertex {QVector3D { 0.5f, 0.5f,-0.5f}, QVector3D{0.988f, 0.890f, 0.541f}},
        /*BTL*/ Vertex {QVector3D {-0.5f, 0.5f,-0.5f}, QVector3D{0.988f, 0.890f, 0.541f}},
        /*BBL*/ Vertex {QVector3D {-0.5f,-0.5f,-0.5f}, QVector3D{0.953f, 0.506f, 0.506f}},
        /*BBR*/ Vertex {QVector3D { 0.5f,-0.5f,-0.5f}, QVector3D{0.953f, 0.506f, 0.506f}},
}};

static constexpr std::array<GLubyte, 36> CUBE_TRIANGLE {{
        // face 1 (front)
    0, 1, 2,
    2, 3, 0,
        // face 2 (back)
    7, 5, 4,
    5, 7, 6,
        // face 3 (top)
    0, 4, 5,
    5, 1, 0,
        // face 4 (bottom)
    3, 2, 6,
    6, 7, 3,
        // face 5 (left)
    2, 1, 5,
    2, 5, 6,
        // face 6 (right)
    0, 3, 7,
    7, 4, 0,
}};

static constexpr std::array<QVector3D, 3> ROTATION_DIRECTION {{
        QVector3D {1.0f, 0.0f, 0.0f},
        QVector3D {0.0f, 1.0f, 0.0f},
        QVector3D {0.0f, 0.0f, 1.0f},
}};

Window::Window(QSurfaceFormat::RenderableType type,
        int majorVersion, int minorVersion) : QOpenGLWindow {},
    m_selectedRotation {0}
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
    m_elementBufferObject.destroy();
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

    glEnable(GL_CULL_FACE);

    m_viewMatrix.setToIdentity();
    m_viewMatrix.translate(0.0f, 0.0f, -3.0f);
    m_viewMatrix.rotate(20.0f, QVector3D {1.0f, 0.0f, 0.0f});
    m_viewMatrix.rotate(20.0f, QVector3D {0.0f, 1.0f, 0.0f});
    m_modelMatrix.setToIdentity();

    // ** Create shaders and keep them bound until VAO is released ** //
    // Keep them bound to resolve uniforms if needed
    m_shaderProgram.create();
    m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader.vert");
    m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader.frag");
    if (m_shaderProgram.link())
        qDebug().noquote() << m_shaderProgram.log();
    m_shaderProgram.bind();

    // ** Create all objects ** //
    m_vertexArrayObject.create();
    m_vertexBufferObject.create();
    m_elementBufferObject = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_elementBufferObject.create();

    // ** Bind VAO ** //
    m_vertexArrayObject.bind();

    // ** Bind and configure VBO states ** //
    m_vertexBufferObject.bind();
    m_vertexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertexBufferObject.allocate(VERTEX.data(), sizeof(VERTEX));

    m_shaderProgram.enableAttributeArray(0);
    m_shaderProgram.setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(),
            Vertex::positionTupleSize(), Vertex::stride());
    m_shaderProgram.enableAttributeArray(1);
    m_shaderProgram.setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(),
            Vertex::colorTupleSize(), Vertex::stride());

    // ** Bind and configure EBO states ** //
    m_elementBufferObject.bind();
    m_elementBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_elementBufferObject.allocate(CUBE_TRIANGLE.data(), sizeof(CUBE_TRIANGLE));

    // ** Release all bound resources ** //
    m_vertexArrayObject.release();
    m_vertexBufferObject.release();
    m_elementBufferObject.release();
    m_shaderProgram.release();
}

void Window::resizeGL(int width, int height)
{
    height = qMax(height, 1);

    glViewport(0, 0, width, height);

    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(45.0f, static_cast<float>(width) / height,
            0.1f, 1000.0f);
}

void Window::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    m_shaderProgram.bind();
    m_shaderProgram.setUniformValue("mvpMatrix",
            m_projectionMatrix * m_viewMatrix * m_modelMatrix);
    m_vertexArrayObject.bind();
    glDrawElements(GL_TRIANGLES, CUBE_TRIANGLE.size(), GL_UNSIGNED_BYTE,
            static_cast<void*>(0));
    m_vertexArrayObject.release();
    m_shaderProgram.release();

    m_modelMatrix.rotate(1.0f, ROTATION_DIRECTION[m_selectedRotation]);
    update();
}

void Window::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        m_selectedRotation = (m_selectedRotation + 1) % ROTATION_DIRECTION.size();
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
