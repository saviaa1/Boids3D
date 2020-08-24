#shader vertex
#version 330 core

layout (location = 0) in vec4 position;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

void main()
{
    color = vec4(0.059f, 0.322f, 0.729f, 1.0f);
}