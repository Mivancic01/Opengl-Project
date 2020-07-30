#ifndef ENGINE_H
#define ENGINE_H

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <iostream>
#include <vector>
#include <map>

#include "../../includes/engineHelper.h"
#include "../../includes/Shader.h"
#include "../../includes/mesh.h"
#include "../../includes/model.h"
#include "../../includes/geometryGenerator.h"
#include "../../includes/camera.h"
#include "../../includes/lightAttributes.h"
#include "../../includes/drawHelper.h"
#include "../../includes/stb_image.h"
#include "../../includes/std_image.h"
#include "../../includes/Water.h"

class Engine
{
public:
    void init();
    void run();

    static Engine* getInstance();

private:
    Engine();
    void initShaders();
    void initGeometry(ShaderType shader);
    void initLightSources();
    void draw();
    void setLights();
    void processInput(GLFWwindow* window);

    float mDeltaTime = 0.0f, mLastFrame = 0.0f;
    GLFWwindow* window;
    std::map<ShaderType, Shader> mShaders;
    std::map<ShaderType, std::vector<BaseMesh*>> mOpaqueMeshes;
    std::map<ShaderType, std::vector<BaseMesh*>> mTransparrentMeshes;
    BaseMesh* mirror;
    BaseMesh* skyBox;
    LightScene mLights;
    Model* model;

    Water water;
};

#endif