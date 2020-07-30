#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 Pos;
out vec2 texCoord;
out vec3 normal;

out VS_OUT
{
     vec3 Pos;
     vec2 texCoord;
     vec3 normal;
}vsOut;

uniform mat4 WVP;
uniform mat4 World;
uniform mat4 WorldInvTransp;

void main()
{
    gl_Position = WVP * vec4(aPos, 1.0);
	vsOut.Pos = vec3(World*vec4(aPos, 1.0));
	vsOut.texCoord = aTexCoords;
	vsOut.normal = mat3(WorldInvTransp) * aNormal;
}

