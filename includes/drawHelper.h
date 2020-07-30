#ifndef DRAWHELPER_H
#define DRAWHELPER_H

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "../../includes/Shader.h"
#include "../../includes/mesh.h"
#include "../../includes/camera.h"
#include "../../includes/lightAttributes.h"

#include <vector>
#include <map>

class DrawHelper
{
public:
    static void drawContainer(Shader shader, std::vector<BaseMesh*>& meshes)
    {
        if (meshes.empty())
            return;

        shader.use();
        shader.setFloat("material.shininess", 32.0f);

        shader.setVec3("viewPos", EngineNamespace::camera.mPosition);
        shader.setVec4("mirrorShade", glm::vec4(1.0f));

        for (auto geom : meshes)
        {
            glm::mat4 PVW = EngineNamespace::camera.GetProjViewMatrix()*geom->mWorld;
            shader.setMat4("WVP", PVW);
            shader.setMat4("World", geom->mWorld);
            glm::mat4 worldInvTransp = glm::transpose(glm::inverse(geom->mWorld));
            shader.setMat4("WorldInvTransp", worldInvTransp);
            geom->draw(shader);
        }
    }

    static void drawTransparentContainer(Shader shader, std::vector<BaseMesh*>& meshes)
    {

        if (meshes.empty())
            return;

        shader.use();
        for (auto geom : meshes)
        {
            glm::mat4 PVW = EngineNamespace::camera.GetProjViewMatrix()*geom->mWorld;
            shader.setMat4("WVP", PVW);
            shader.setMat4("World", geom->mWorld);
            geom->draw(shader);
        }
    }

    static void drawMirroredContainer(Shader shader, std::vector<BaseMesh*>& meshes, glm::vec3 mirrorPos)
    {
        if (meshes.empty())
            return;

        glStencilFunc(GL_EQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDepthMask(GL_TRUE);
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

        shader.use();
        shader.setFloat("material.shininess", 32.0f);
        shader.setVec4("mirrorShade", glm::vec4(0.3f));
        shader.setVec3("viewPos", EngineNamespace::camera.mPosition);

        for (auto geom : meshes)
        {
            float delta = 2 * (mirrorPos.x - geom->mPos.x);
            glm::mat4 translation = glm::translate(geom->translation, glm::vec3(delta, 0.1f, 0.0f));
            glm::mat4 world = translation*geom->rotation*geom->scale;
            glm::mat4 PVW = EngineNamespace::camera.GetProjViewMatrix()*world;
            shader.setMat4("WVP", PVW);
            shader.setMat4("World", world);
            glm::mat4 worldInvTransp = glm::transpose(glm::inverse(world));
            shader.setMat4("WorldInvTransp", worldInvTransp);
            geom->draw(shader);
        }
    }

    static void drawMesh(Shader shader, BaseMesh* mesh, bool useStencil, bool skybox)
    {
        if (useStencil)
        {
            glEnable(GL_STENCIL_TEST);
            glStencilFunc(GL_ALWAYS, 1, 0xFF);
            glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
            glStencilMask(0xFF);
            glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
            glDepthMask(GL_FALSE);
            glClear(GL_STENCIL_BUFFER_BIT);
        }
        shader.use();
        shader.setFloat("material.shininess", 32.0f);

        shader.setVec3("viewPos", EngineNamespace::camera.mPosition);

        glm::mat4 PVW;
        if (skybox)
        {
            glm::mat4 proj = EngineNamespace::camera.GetProjMatrix();
            glm::mat4 view = glm::mat4(glm::mat3(EngineNamespace::camera.GetViewMatrix()));
            PVW = proj*view;
        }
        else
        {
            PVW = EngineNamespace::camera.GetProjViewMatrix()*mesh->mWorld;
            shader.setMat4("World", mesh->mWorld);
            glm::mat4 worldInvTransp = glm::transpose(glm::inverse(mesh->mWorld));
            shader.setMat4("WorldInvTransp", worldInvTransp);
        }
        shader.setMat4("WVP", PVW);
        mesh->draw(shader);
    }
};

#endif