#version 330 core

layout(location = 0) in vec3 aPos;

out float vHeight; // send Y value to fragment shader

uniform mat4 uMVP;

void main()
{
    gl_Position = uMVP * vec4(aPos, 1.0);
    vHeight = aPos.y; // pass Y value
}