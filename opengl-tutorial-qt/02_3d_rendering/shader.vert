#version 330 core
layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 color;

out vec3 vertexColor;

uniform mat4 mvpMatrix;

void main()
{
    gl_Position = mvpMatrix * vec4(vertex, 1.0f);
    vertexColor = color;
}
