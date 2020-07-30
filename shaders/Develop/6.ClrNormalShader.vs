#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aClr;
layout (location = 2) in vec3 aNormal;

out vec4 color;
out vec3 normal;

uniform mat4 WVP;
uniform mat4 WorldInvTransp;

void main()
{
    gl_Position = WVP * vec4(aPos, 1.0);
	color = aClr;
	normal = mat3(WorldInvTransp) * aNormal;
}

