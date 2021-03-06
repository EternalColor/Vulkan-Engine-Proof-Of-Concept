#version 450
#extension GL_ARB_seperate_shader_objects : enable

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec3 inColor;

layout(location = 0) out vec3 fragmentColor;

void main()
{
    gl_Position = vec4(inPosition, 0.0, 1.0);
    fragmentColor = inColor;
}