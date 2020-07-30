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

struct SpotLight
{
    float cutOff;
	float outerCutOff;

    vec3 position;
	vec3 direction;
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
uniform bool useSpotlight;
uniform DirectionalLight dirLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;
uniform vec4 mirrorShade;

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir, vec3 ambient, vec3 diffuse, vec3 specular);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 ambient, vec3 diffuse, vec3 specular);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 ambient, vec3 diffuse, vec3 specular);

void main()
{
    vec4 diffuse, specular;
	vec3 result;
	diffuse = texture(material.texture_diffuse1, texCoord);
	specular = texture(material.texture_specular1, texCoord);

	vec3 norm = normalize(normal);
	vec3 viewDir = normalize(viewPos - Pos);
    result = CalcDirLight(dirLight, norm, viewDir, vec3(diffuse), vec3(diffuse), vec3(specular));
    result += CalcPointLight(pointLight, norm, Pos, viewDir, vec3(diffuse), vec3(diffuse), vec3(specular));
	bool a = true;
	if(useSpotlight == true)
	    result += CalcSpotLight(spotLight, norm, Pos, viewDir, vec3(diffuse), vec3(diffuse), vec3(specular));
	FragColor = vec4(result, 1.0f)*mirrorShade;
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
    vec3 lightDir = normalize(light.position - fragPos);

	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	float distance = length(light.position - fragPos);
	float att = 1.0/(light.attenuation.x + light.attenuation.y*distance + light.attenuation.z*distance*distance);

	vec3 resAmbient = light.ambient*ambient;
	vec3 resDiffuse = light.diffuse*diff*diffuse;
	vec3 resSpecular = light.specular*spec*specular;

	resAmbient*=att;
	resDiffuse*=att;
	resSpecular*=att;

	return (resAmbient + resDiffuse + resSpecular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 ambient, vec3 diffuse, vec3 specular)
{
	vec3 lightDir = normalize(light.position - fragPos);

	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	float distance = length(light.position - fragPos);
	float att = 1.0/(light.attenuation.x + light.attenuation.y*distance + light.attenuation.z*distance*distance);

	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff)/epsilon, 0.0, 1.0);

	vec3 resAmbient = light.ambient*ambient;
	vec3 resDiffuse = light.diffuse*diff*diffuse;
	vec3 resSpecular = light.specular*spec*specular;

	resAmbient*=att*intensity;
	resDiffuse*=att*intensity;
	resSpecular*=att*intensity;

	return (resAmbient + resDiffuse + resSpecular);
}