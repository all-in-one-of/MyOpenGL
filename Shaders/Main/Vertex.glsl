#version 330 core
layout (location = 0) in vec3 aPos; // Input vertex position

uniform float ElapsedTime;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y + sin(ElapsedTime) * .1, aPos.z, 1.0);
}