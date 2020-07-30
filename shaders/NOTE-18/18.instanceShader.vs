#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 aInstanceMatrix;

out vec2 texCoord;

uniform mat4 WVP;

void main()
{
    gl_Position = WVP * aInstanceMatrix * vec4(aPos, 1.0);
	texCoord = aTexCoords;
}

