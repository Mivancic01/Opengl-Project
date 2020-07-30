#version 460 core

out vec4 FragColor;

in vec2 texCoord;
in vec3 normal;

uniform sampler2D sampler;

void main()
{
    FragColor = texture(sampler, texCoord);
}

