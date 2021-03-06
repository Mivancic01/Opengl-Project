#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aClr;

out vec4 color;

uniform mat4 WVP;

void main()
{
    gl_Position = WVP * vec4(aPos, 1.0);
	color = aClr;
}

