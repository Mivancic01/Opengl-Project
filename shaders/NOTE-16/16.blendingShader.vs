#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec3 Pos;
out vec2 texCoord;

uniform mat4 WVP;
uniform mat4 World;

void main()
{
    gl_Position = WVP * vec4(aPos, 1.0);
	Pos = vec3(World*vec4(aPos, 1.0));
	texCoord = aTexCoords;
}

