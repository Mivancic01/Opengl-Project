#version 460 core

in vec4 color;

out vec4 FragColor;

uniform vec4 mirrorShade;

void main()
{
    FragColor = vec4(1.0f)*mirrorShade;
}

