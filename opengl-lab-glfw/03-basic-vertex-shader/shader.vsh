#version 330 core
layout(location = 0) in vec3 vertex;

uniform bool flipHorizontal;
uniform bool flipVertical;
uniform float offsetHorizontal;
uniform float offsetVertical;

void main()
{
    vec4 outVertex = vec4(vertex, 1.0f);
    if (flipHorizontal)
        outVertex.x = -outVertex.x;
    if (flipVertical)
        outVertex.y = -outVertex.y;
    outVertex += vec4(offsetHorizontal, offsetVertical, 0.0f, 0.0f);

    gl_Position = outVertex;
}
