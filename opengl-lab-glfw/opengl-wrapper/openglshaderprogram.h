#pragma once

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#include "glad/glad.h"
#pragma clang diagnostic pop

#include <string>
#include <list>

class OpenGLShaderProgram {
public:
    enum Type : GLenum {
        Vertex = GL_VERTEX_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
    };

    virtual ~OpenGLShaderProgram();

    void addShader(Type type, const std::string &fileName);
    void link();

    void use();

private:
    GLuint              m_shaderProgram {0};
    std::list<GLuint>   m_shader;
    bool                m_linked {false};

    void create();

    std::string loadShaderSource(const std::string &fileName) const;
    std::string getShaderCompileError(GLuint shader) const;
    std::string getProgramLinkError(GLuint program) const;

    std::string toString(Type type) const;
};
