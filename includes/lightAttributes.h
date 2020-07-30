#ifndef LIGHTATTRIBUTES_H
#define LIGHTATTRIBUTES_H

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <vector>

#include "Shader.h"

#define CONSTANT 1.0f
#define LINEAR 0.09f
#define QUADRATIC 0.032f

struct DirectionalLight
{
    glm::vec3 direction;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    DirectionalLight() {};
    DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
        : direction(direction), ambient(ambient), diffuse(diffuse), specular(specular) {};
};

struct PointLight
{
    glm::vec3 position;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    PointLight() {};
    PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
        : ambient(ambient), diffuse(diffuse), specular(specular) {};
};

struct SpotLight
{
    float cutOff;
    float outerCutOff;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    SpotLight() {};
    SpotLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float cutOff, float outerCutOff)
        : ambient(ambient), diffuse(diffuse), specular(specular), cutOff(cutOff), outerCutOff(outerCutOff) {};
};

class LightScene
{
public:
    bool toggleLight = false, keyReleased = false;

    LightScene() {};

    void initLightSources(
        std::vector<DirectionalLight> dirLights,
        std::vector<PointLight> pointLights,
        std::vector<SpotLight> spotLights)
    {
        mDirLights = dirLights;
        mPointLights = pointLights;
        mSpotLights = spotLights;
    }

    void updatePointLightPosition(std::vector<glm::vec3> pos)
    {
        for (int i = 0; i < pos.size(); i++)
            mPointLights[i].position = pos[i];
    }

    void updatePointLightPosition(glm::vec3 pos)
    {
        mPointLights[0].position = pos;
    }

    void setLights(Shader shader, glm::vec3 position, glm::vec3 spotlightDirection = glm::vec3(0.0f, 0.0f, -1.0f))
    {
        if (toggleLight != keyReleased)
        {
            if (keyReleased)
            {
                useSpotlight = !useSpotlight;
                toggleLight = false;
                keyReleased = false;
            }

            keyReleased = toggleLight;
        }

        shader.setBool("useSpotlight", useSpotlight);
        for (int i = 0; i < mDirLights.size(); i++)
        {
            std::string name;
            if(mDirLights.size() == 1)
                name = "dirLight.";
            else
                name = "dirLight[" + std::to_string(i) + "].";

            shader.setVec3(name + "direction", mDirLights[i].direction);
            shader.setVec3(name + "ambient", mDirLights[i].ambient);
            shader.setVec3(name + "diffuse", mDirLights[i].diffuse);
            shader.setVec3(name + "specular", mDirLights[i].specular);
        }

        for (int i = 0; i < mPointLights.size(); i++)
        {
            std::string name;
            if (mPointLights.size() == 1)
                name = "pointLight.";
            else
                name = "pointLight[" + std::to_string(i) + "].";

            shader.setVec3(name + "position", mPointLights[i].position);
            shader.setVec3(name + "ambient", mPointLights[i].ambient);
            shader.setVec3(name + "diffuse", mPointLights[i].diffuse);
            shader.setVec3(name + "specular", mPointLights[i].specular);
            shader.setVec3(name + "attenuation", glm::vec3(CONSTANT, LINEAR, QUADRATIC));
        }

        if (useSpotlight)
            for (int i = 0; i < mSpotLights.size(); i++)
            {
                std::string name;
                if (mSpotLights.size() == 1)
                    name = "spotLight.";
                else
                    name = "spotLight[" + std::to_string(i) + "].";

                shader.setVec3(name + "position", position);
                shader.setVec3(name + "direction", spotlightDirection);

                shader.setVec3(name + "ambient", mSpotLights[i].ambient);
                shader.setVec3(name + "diffuse", mSpotLights[i].diffuse);
                shader.setVec3(name + "specular", mSpotLights[i].specular);

                shader.setFloat(name + "cutOff", mSpotLights[i].cutOff);
                shader.setFloat(name + "outerCutOff", mSpotLights[i].outerCutOff);
                shader.setVec3(name + "attenuation", glm::vec3(CONSTANT, LINEAR, QUADRATIC));
            }
        
    }

private:
    bool useSpotlight = true;

    std::vector<DirectionalLight> mDirLights;
    std::vector<PointLight> mPointLights;
    std::vector<SpotLight> mSpotLights;
};
#endif