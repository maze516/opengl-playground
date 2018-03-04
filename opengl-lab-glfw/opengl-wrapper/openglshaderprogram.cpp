#include "openglshaderprogram.h"

#include "logger.h"

#include <array>
#include <cassert>
#include <exception>
#include <fstream>
#include <sstream>
#include <memory>

OpenGLShaderProgram::~OpenGLShaderProgram()
{
    if (!m_shaderProgram)
        return;

    while (!m_shader.empty()) {
        auto shader = m_shader.front();
        glDetachShader(m_shaderProgram, shader);
        DEBUG("OpenGLShaderProgram: detached shader #" << shader <<
                " from program #" << m_shaderProgram);
        glDeleteShader(shader);
        DEBUG("OpenGLShaderProgram: deleted shader #" << shader);
        m_shader.pop_front();
    }

    glDeleteProgram(m_shaderProgram);
    DEBUG("OpenGLShaderProgram: deleted shader program #" << m_shaderProgram);
}

void OpenGLShaderProgram::addShader(Type type, const std::string &fileName)
{
    if (!m_shaderProgram)
        create();

    auto shader = glCreateShader(type);
    auto shaderSourcePtr = loadShaderSource(fileName).c_str();
    glShaderSource(shader, 1, &shaderSourcePtr, nullptr);

    glCompileShader(shader);

    GLint result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (!result) {
        DEBUG("OpenGLShaderProgram: compilation error of shader #" << shader);
        DEBUG(getShaderCompileError(shader));
        throw std::runtime_error("OpenGLShaderProgram: compilation error of shader #" +
                std::to_string(shader));
    }

    m_shader.push_back(shader);
    DEBUG("OpenGLShaderProgram: created " << toString(type) << " shader #" <<
            shader << " [" << fileName << "]");
}

void OpenGLShaderProgram::link()
{
    assert(m_shaderProgram != 0);
    m_linked = false;

    for (const auto &shader: m_shader) {
        glAttachShader(m_shaderProgram, shader);
        DEBUG("OpenGLShaderProgram: attached shader #" << shader <<
              " to program #" << m_shaderProgram);
    }

    glLinkProgram(m_shaderProgram);
    GLint result;
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &result);
    if (!result) {
        DEBUG("OpenGLShaderProgram: link error of program #" << m_shaderProgram);
        DEBUG(getProgramLinkError(m_shaderProgram));
        throw std::runtime_error("OpenGLShaderProgram: link error of program #" +
                std::to_string(m_shaderProgram));
    }

    DEBUG("OpenGLShaderProgram: linked program #" << m_shaderProgram);
    m_linked = true;
}

void OpenGLShaderProgram::use()
{
    assert(m_shaderProgram);

    if (!m_linked)
        throw std::runtime_error("OpenGLShaderProgram: program #" +
                std::to_string(m_shaderProgram) + " is not linked");

    glUseProgram(m_shaderProgram);
}

void OpenGLShaderProgram::create()
{
    m_shaderProgram = glCreateProgram();
    DEBUG("OpenGLShaderProgram: created program #" << m_shaderProgram);
}

std::string OpenGLShaderProgram::loadShaderSource(
        const std::string &fileName) const
{
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    file.open(fileName);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

std::string OpenGLShaderProgram::getShaderCompileError(GLuint shader) const
{
    GLsizei errorMsgSize;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorMsgSize);
    auto errorMsg = std::make_unique<GLchar[]>(
            static_cast<size_t>(errorMsgSize));
    glGetShaderInfoLog(shader, errorMsgSize,
            nullptr, errorMsg.get());
    return std::string(errorMsg.get());
}

std::string OpenGLShaderProgram::getProgramLinkError(GLuint program) const
{
    GLsizei errorMsgSize;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &errorMsgSize);
    auto errorMsg = std::make_unique<GLchar[]>(
            static_cast<size_t>(errorMsgSize));
    glGetProgramInfoLog(program, errorMsgSize,
            nullptr, errorMsg.get());
    return std::string(errorMsg.get());
}

std::string OpenGLShaderProgram::toString(Type type) const
{
    switch (type) {
        case Vertex:
            return "vertex";
        case Fragment:
            return "fragment";
    }
}
