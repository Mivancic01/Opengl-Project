#version 460 core

out vec4 FragColor;

struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
	float shininess;
};

struct DirectionalLight
{
    vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
    vec3 position;
	vec3 attenuation;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 Pos;
in vec2 texCoord;
in vec3 normal;

uniform Material material;
uniform vec3 viewPos;
uniform DirectionalLight dirLight;
uniform PointLight pointLight;

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir, vec3 ambient, vec3 diffuse, vec3 specular);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 ambient, vec3 diffuse, vec3 specular);

void main()
{
    vec4 diffuse, specular;
	diffuse = texture(material.texture_diffuse1, texCoord);
	specular = texture(material.texture_specular1, texCoord);

	vec3 norm = normalize(normal);
	vec3 viewDir = normalize(viewPos - Pos);
    vec3 result = CalcDirLight(dirLight, norm, viewDir, vec3(diffuse), vec3(diffuse), vec3(specular));
    
	FragColor = vec4(result, 1.0f);
	//FragColor = vec4(viewDir, 1.0f);
}

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir, vec3 ambient, vec3 diffuse, vec3 specular)
{
    vec3 lightDir = normalize(-light.direction);

	float diff = max(dot(normal, lightDir), 0.0f);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	return (light.ambient*ambient + light.diffuse*diff*diffuse + light.specular*spec*specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 ambient, vec3 diffuse, vec3 specular)
{
    vec3 result;
	return result;
}