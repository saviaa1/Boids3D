#shader vertex
#version 330 core

void main()
{
    gl_Position = vec4(position, 1.0);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

void main()
{
    color = vec4(0.9f, 0.5f, 0.0f, 1.0f);
}