#version 460 core

out vec4 FragColor;

struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
	float shininess;
};

in vec2 texCoord;
in vec3 normal;

uniform Material material;


void main()
{
    FragColor = texture(material.texture_diffuse1, texCoord);
	vec4 spec = texture(material.texture_specular1, texCoord);
}

