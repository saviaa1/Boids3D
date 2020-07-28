#shader vertex
#version 330 core

void main()
{
    gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

void main()
{
    color = vec4(1.0, 0.0, 0.0, 1.0);
};