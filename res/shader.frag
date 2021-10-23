#version 450
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) out vec4 color;

void main()
{
    color = vec4(0.84, 0.72, 0.04, 1);
}