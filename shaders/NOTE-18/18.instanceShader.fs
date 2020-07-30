#version 460 core

out vec4 FragColor;

struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
	float shininess;
};

in vec2 texCoord;

uniform Material material;

void main()
{
    FragColor = texture(material.texture_diffuse1, texCoord);
}