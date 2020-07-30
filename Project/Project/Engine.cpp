#include "Engine.h"

Engine* Engine::getInstance()
{
    static Engine* instance = new Engine();
    return instance;
}

Engine::Engine()
{

}

void Engine::init()
{
    EngineNamespace::camera.Init(glm::vec3(1.5f, 1.5f, 4.0f));
    EngineNamespace::camera;
    window = EngineNamespace::initWindow();

    initShaders();
    for (auto shader : mShaders)
        initGeometry(shader.first);

    initLightSources();
}

void Engine::initShaders()
{
    Shader basicShader("../../shaders/NOTE-18/18.basicShader.vs", "../../shaders/NOTE-18/18.basicShader.fs");
    mShaders[ShaderType::BASIC_SHADER] = basicShader;

    Shader clrShader("../../shaders/NOTE-18/18.ClrShader.vs", "../../shaders/NOTE-18/18.ClrShader.fs");
    mShaders[ShaderType::CLR_SHADER] = clrShader;

    Shader texShader("../../shaders/NOTE-18/18.blendingShader.vs", "../../shaders/NOTE-18/18.blendingShader.fs");
    mShaders[ShaderType::TEX_SHADER] = texShader;

    Shader texNormalShader("../../shaders/NOTE-18/18.lightingShader.vs", "../../shaders/NOTE-18/18.lightingShader.fs");
    mShaders[ShaderType::TEX_NORMAL_SHADER] = texNormalShader;

    /*Shader texNormalShader("../../shaders/NOTE-17/17.lightingShader.vs", "../../shaders/NOTE-17/17.lightingShader.fs", "../../shaders/NOTE-17/17.explodingShader.gs");
    mShaders[ShaderType::TEX_NORMAL_SHADER] = texNormalShader;*/

    Shader skyBoxShader("../../shaders/NOTE-18/18.skybox.vs", "../../shaders/NOTE-18/18.skybox.fs");
    mShaders[ShaderType::SKYBOX_SHADER] = skyBoxShader;

    Shader instanceShader("../../shaders/NOTE-18/18.instanceShader.vs", "../../shaders/NOTE-18/18.instanceShader.fs");
    mShaders[ShaderType::INSTANCE_TEX_SHADER] = instanceShader;

    //WATER
    // Shader waterShader("../../shaders/waterVertShader.vs", "../../shaders/waterFragShader.fs");
   // water.init(waterShader.mProgramID);
}

void Engine::initGeometry(ShaderType shader)
{
    std::vector<Texture> textures;
    const char* texPath = "../../resources/textures/wood.png";
    const char* windowTexPath = "../../resources/textures/window.png";
    const char* diffusePath = "../../resources/textures/container2.png";
    const char* specularPath = "../../resources/textures/container2_specular.png";
    std::vector<std::string> skyboxFaces 
    {
        "../../resources/textures/skybox/right.jpg",
        "../../resources/textures/skybox/left.jpg",
        "../../resources/textures/skybox/top.jpg",
        "../../resources/textures/skybox/bottom.jpg",
        "../../resources/textures/skybox/front.jpg",
        "../../resources/textures/skybox/back.jpg"
    };
    glm::mat4 world = glm::mat4(1.0f);
    glm::vec4 identityVec = glm::vec4(1.0f);
    BaseMesh* mesh;

    std::vector<BaseMesh*> baseMeshVec;
    std::vector<BaseMesh*> transparentVec;
    switch (shader)
    {
    case ShaderType::BASIC_SHADER:
        mirror =GeometryGenerator::generatePlane(shader, textures);
        mirror->translation = glm::translate(world, glm::vec3(-5.0f, 0.0f, -4.0f));
        mirror->mPos = mirror->translation*identityVec;
        mirror->rotation = glm::rotate(world, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        mirror->scale = glm::scale(world, glm::vec3(0.2f));
        mirror->setWorldMatrix();
        break;
    case ShaderType::CLR_SHADER:
        mesh = GeometryGenerator::generateCube(shader, textures);
        mesh->translation = glm::translate(world, glm::vec3(0.0f, 0.0f, 2.0f));
        mesh->scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
        mesh->setWorldMatrix();
        baseMeshVec.push_back(mesh);
        break;
    case ShaderType::CLR_NORMAL_SHADER:
        break;
    case ShaderType::TEX_SHADER:
        textures.push_back(Texture(EngineNamespace::createTex(windowTexPath), "texture_diffuse", windowTexPath));
        textures.push_back(Texture(EngineNamespace::createTex(windowTexPath), "texture_specular", windowTexPath));
        mesh = GeometryGenerator::generateQuad(shader, textures);
        mesh->translation = glm::translate(world, glm::vec3(0.0f, -2.0f, 5.0f));
        //mesh->scale = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f));
        mesh->setWorldMatrix();
        transparentVec.push_back(mesh);
        break;
    case ShaderType::TEX_NORMAL_SHADER:
        textures.push_back(Texture(EngineNamespace::createTex(diffusePath), "texture_diffuse", diffusePath));
        textures.push_back(Texture(EngineNamespace::createTex(specularPath), "texture_specular", specularPath));

        mesh = GeometryGenerator::generateCube(shader, textures);
        mesh->translation = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, -2.0f, -6.0f));
        mesh->setWorldMatrix();
        baseMeshVec.push_back(mesh);

        model = new Model("../../resources/objects/nanosuit/nanosuit.obj", shader);
        model->translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, -2.0f));
        model->scale = glm::scale(world, glm::vec3(0.2f));
        model->setWorldMatrix();
        baseMeshVec.push_back(model);

        model = new Model("../../resources/objects/planet/planet.obj", shader);
        model->translation = glm::translate(glm::mat4(1.0f), glm::vec3(50.0f, -2.0f, -50.0f));
        model->rotation = glm::rotate(world, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model->scale = glm::scale(world, glm::vec3(7.0f));
        model->setWorldMatrix();
        baseMeshVec.push_back(model);

        textures.clear();
        textures.push_back(Texture(EngineNamespace::createTex(texPath), "texture_diffuse", texPath));
        textures.push_back(Texture(EngineNamespace::createTex(texPath), "texture_specular", texPath));

        mesh = GeometryGenerator::generatePlane(shader, textures);
        mesh->translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, 0.0f));
        mesh->setWorldMatrix();
        baseMeshVec.push_back(mesh);
        break;
    case ShaderType::SKYBOX_SHADER:
        textures.push_back(Texture(EngineNamespace::createCubeMap(skyboxFaces), "texture_cubemap", "../../resources/textures/skybox"));
        skyBox = GeometryGenerator::createSkybox(ShaderType::SKYBOX_SHADER, textures);
        skyBox->setWorldMatrix();
        break;
    case ShaderType::INSTANCE_TEX_SHADER:
        model = new Model("../../resources/objects/rock/rock.obj", shader);
        model->translation = glm::translate(glm::mat4(1.0f), glm::vec3(50.0f, -2.0f, -50.0f));
        model->setWorldMatrix();
        baseMeshVec.push_back(model);

        break;
    }

    mOpaqueMeshes[shader] = baseMeshVec;
    mTransparrentMeshes[shader] = transparentVec;
}

void Engine::initLightSources()
{
    glm::vec3 ambient(0.5f);
    glm::vec3 diffuse(0.8f);
    glm::vec3 specular(1.0f);
    glm::vec3 direction = glm::vec3(1.0f, -1.0f, -1.0f);
    float cutOff = glm::cos(glm::radians(12.5f)), outerCutOff = glm::cos(glm::radians(15.0f));

    std::vector<DirectionalLight> dirLight =
    {
        DirectionalLight(direction, ambient, diffuse, specular)
    };

    std::vector<PointLight> pointLight =
    {
        PointLight(ambient, diffuse, specular)
    };

    std::vector<SpotLight> spotLight =
    {
        SpotLight(ambient, diffuse, specular, cutOff, outerCutOff)
    };

    mLights.initLightSources(dirLight, pointLight, spotLight);
}

void Engine::run()
{
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window))
    {
        mDeltaTime = glfwGetTime() - mLastFrame;
        mLastFrame = glfwGetTime();

        std::cout << "New Matrix"<<std::endl;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
                std::cout << EngineNamespace::camera.GetProjViewMatrix()[i][j]<<", ";
            std::cout<< std::endl;
        }

        processInput(window);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |GL_STENCIL_BUFFER_BIT);

        glm::vec3 translate = glm::vec3(0.0f, glm::sin(glfwGetTime())*0.04f, glm::sin(glfwGetTime())*0.04f);
        glm::vec3 pos;
        for (auto mesh : mOpaqueMeshes[ShaderType::CLR_SHADER]) {
            mesh->translation = glm::translate(mesh->translation, translate);
            mesh->setWorldMatrix();
            mesh->mPos = mesh->translation*glm::vec4(1.0f);
            pos = glm::vec3(mesh->mPos.x, mesh->mPos.y, mesh->mPos.z);
            mLights.updatePointLightPosition(pos);
        }

        draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    for (auto meshVec : mOpaqueMeshes)
        for (auto mesh : meshVec.second)
            mesh->cleanUp();
    for (auto meshVec : mTransparrentMeshes)
        for (auto mesh : meshVec.second)
            mesh->cleanUp();
    mirror->cleanUp();
    skyBox->cleanUp();

    glfwTerminate();
}

void Engine::draw()
{
    setLights();
    //mShaders[ShaderType::TEX_NORMAL_SHADER].setFloat("time", glfwGetTime());

    glDepthFunc(GL_LEQUAL);
    DrawHelper::drawMesh(mShaders[ShaderType::SKYBOX_SHADER], skyBox, false, true);
    glDepthFunc(GL_LESS);

    for (auto shader : mShaders)
    {
        if (shader.first == TEX_NORMAL_SHADER)
        {
            DrawHelper::drawContainer(mShaders[INSTANCE_TEX_SHADER], mOpaqueMeshes[INSTANCE_TEX_SHADER]);
            DrawHelper::drawContainer(shader.second, mOpaqueMeshes[shader.first]);
        }
        else if (shader.first == INSTANCE_TEX_SHADER)
            continue;
        else
            DrawHelper::drawContainer(shader.second, mOpaqueMeshes[shader.first]);

    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);
    for (auto shader : mShaders)
        DrawHelper::drawTransparentContainer(shader.second, mTransparrentMeshes[shader.first]);
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);

    DrawHelper::drawMesh(mShaders[ShaderType::BASIC_SHADER], mirror, true, false);
    
    for (auto shader : mShaders)
    {
        if (shader.first == TEX_NORMAL_SHADER)
        {
            DrawHelper::drawMirroredContainer(mShaders[INSTANCE_TEX_SHADER], mOpaqueMeshes[INSTANCE_TEX_SHADER], mirror->mPos);
            DrawHelper::drawMirroredContainer(shader.second, mOpaqueMeshes[shader.first], mirror->mPos);
        }
        else if (shader.first == INSTANCE_TEX_SHADER)
            continue;
        else
            DrawHelper::drawMirroredContainer(shader.second, mOpaqueMeshes[shader.first], mirror->mPos);
    }
       // DrawHelper::drawMirroredContainer(shader.second, mOpaqueMeshes[shader.first], mirror->mPos);
    glDisable(GL_STENCIL_TEST);

    
}

void Engine::setLights()
{
    mLights.setLights(mShaders[ShaderType::TEX_NORMAL_SHADER], EngineNamespace::camera.mPosition, EngineNamespace::camera.mFront);
    mLights.setLights(mShaders[ShaderType::INSTANCE_TEX_SHADER], EngineNamespace::camera.mPosition, EngineNamespace::camera.mFront);
}

void Engine::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        EngineNamespace::camera.ProcessKeyboard(FORWARD, mDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        EngineNamespace::camera.ProcessKeyboard(BACKWARD, mDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        EngineNamespace::camera.ProcessKeyboard(LEFT, mDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        EngineNamespace::camera.ProcessKeyboard(RIGHT, mDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        mLights.toggleLight = true;
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE)
        mLights.toggleLight = false;
}