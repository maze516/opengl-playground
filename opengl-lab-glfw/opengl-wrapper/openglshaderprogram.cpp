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
    auto shaderSource = loadShaderSource(fileName);
    auto shaderSourcePtr = shaderSource.c_str();
    glShaderSource(shader, 1, &shaderSourcePtr, nullptr);

    glCompileShader(shader);

    GLint result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (!result) {
        INFO("OpenGLShaderProgram: compilation error of shader #" <<
                shader << " [" << fileName << "]");
        INFO(getShaderCompileError(shader));
        throw std::runtime_error("OpenGLShaderProgram compilation error");
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
        INFO("OpenGLShaderProgram: link error of program #" << m_shaderProgram);
        INFO(getProgramLinkError(m_shaderProgram));
        throw std::runtime_error("OpenGLShaderProgram: link error");
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

void OpenGLShaderProgram::setUniform(const std::string &name, bool value) const
{
    assert(m_shaderProgram);

    auto location = glGetUniformLocation(m_shaderProgram, name.c_str());
    if (location < 0)
        throw std::runtime_error("OpenGLShaderProgram: program #" +
                std::to_string(m_shaderProgram) + " has no uniform '" +
                name + "'");
    glUniform1i(location, static_cast<int>(value));
}

void OpenGLShaderProgram::setUniform(const std::string &name, float value) const
{
    assert(m_shaderProgram);

    auto location = glGetUniformLocation(m_shaderProgram, name.c_str());
    if (location < 0)
        throw std::runtime_error("OpenGLShaderProgram: program #" +
                std::to_string(m_shaderProgram) + " has no uniform '" +
                name + "'");
    glUniform1f(location, value);
}

void OpenGLShaderProgram::setUniform(const std::string &name, float x,
        float y, float z) const
{
    assert(m_shaderProgram);

    auto location = glGetUniformLocation(m_shaderProgram, name.c_str());
    if (location < 0)
        throw std::runtime_error("OpenGLShaderProgram: program #" +
                std::to_string(m_shaderProgram) + " has no uniform '" +
                name + "'");
    glUniform3f(location, x, y, z);

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
