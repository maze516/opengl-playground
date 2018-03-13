#version 330 core
in vec4 vertexColor;

out vec4 FragColor;

uniform bool uniformColor;
uniform vec3 triangleColor;

void main()
{
    if (uniformColor)
        FragColor = vec4(triangleColor, 1.0f);
    else
        FragColor = vertexColor;
}
