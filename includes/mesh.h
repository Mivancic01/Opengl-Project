#ifndef MESH_H
#define MESH_H

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Shader.h"

#include <iostream>
#include <vector>
#include <string>



struct Vertex
{
    glm::vec3 pos;
    glm::vec4 color;
    glm::vec3 normal;
    glm::vec2 texCoord;
    glm::vec3 tangent;
    glm::vec3 bitangent;

    Vertex() {};

    Vertex(glm::vec3 inPos, glm::vec4 inColor, glm::vec3 inNormal,
        glm::vec2 inTexCoord, glm::vec3 inTangent, glm::vec3 inBitangent) :
        pos(inPos), color(inColor), normal(inNormal), texCoord(inTexCoord),
        tangent(inTangent), bitangent(inBitangent) {};

    Vertex(float x, float y, float z, float r, float g, float b, float a, float nx, float ny, float nz,
        float u, float v, float tx, float ty, float tz, float bx, float by, float bz) :
        pos(glm::vec3(x, y, z)), color(glm::vec4(r, g, b, a)), normal(glm::vec3(nx, ny, nz)), 
        texCoord(glm::vec2(u, v)), tangent(glm::vec3(tx, ty, tz)), bitangent(glm::vec3(bx, by, bz)) {};

    void setPos(glm::vec3 vec)
    {
        pos = vec;
    }

    void setColor(glm::vec4 vec)
    {
        color = vec;
    }

    void setNormal(glm::vec3 vec)
    {
        normal = vec;
    }

    void setTexCoord(glm::vec2 vec)
    {
        texCoord = vec;
    }

    void setTangent(glm::vec3 vec)
    {
        tangent = vec;
    }

    void setBitangent(glm::vec3 vec)
    {
        bitangent = vec;
    }
};

struct Texture
{
    unsigned int id;
    std::string type;
    std::string path;

    Texture() {};
    Texture(unsigned int id, std::string type, std::string path)
    {
        this->id = id;
        this->type = type;
        this->path = path;
    }
};

class BaseMesh
{
public:
    glm::mat4 mWorld;
    glm::vec4 mPos;
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotation = glm::mat4(1.0f);
    glm::mat4 translation = glm::mat4(1.0f);

    virtual void draw(Shader shader) = 0;
    virtual void cleanUp() = 0;
    void setWorldMatrix()
    {
        mWorld = translation*rotation*scale;
        mPos = translation*glm::vec4(1.0f);
    }
};

class Mesh : public BaseMesh
{
public:
    unsigned int mVAO, mVBO, mEBO, instanceVBO;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, ShaderType type)
    {
        this->mVertices = vertices;
        this->mIndices = indices;
        this->mTextures = textures;
        this->mType = type;
        this->mWorld = glm::mat4(1.0f);
        this->mAmount = 1000;

        setupMesh(false);
    }

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, ShaderType type, unsigned int amount)
    {
        this->mVertices = vertices;
        this->mIndices = indices;
        this->mTextures = textures;
        this->mType = type;
        this->mWorld = glm::mat4(1.0f);
        this->mAmount = amount;

        setupMesh(true);
    }

    void draw(Shader shader)
    {
        shader.use();

        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;

        for (unsigned int i = 0; i < mTextures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);

            std::string number;
            std::string name = mTextures[i].type;
            if (!strcmp(mTextures[i].type.c_str(), "texture_diffuse"))
                number = std::to_string(diffuseNr++);
            else if(!strcmp(mTextures[i].type.c_str(), "texture_specular"))
                number = std::to_string(specularNr++);
            else if (!strcmp(mTextures[i].type.c_str(), "texture_cubemap"))
            {
                name = "cubemap" + (i+1);
                glUniform1i(glGetUniformLocation(shader.mProgramID, (name).c_str()), i);
                glBindTexture(GL_TEXTURE_CUBE_MAP, mTextures[i].id);
                continue;
            }

            name = "material." + name + number;
            glUniform1i(glGetUniformLocation(shader.mProgramID, (name).c_str()), i);
            glBindTexture(GL_TEXTURE_2D, mTextures[i].id);

        }
        glBindVertexArray(mVAO);
        if (mType == INSTANCE_TEX_SHADER)
            glDrawElementsInstanced(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0, mAmount);
        else
            glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
    }

    void cleanUp()
    {
        glDeleteVertexArrays(1, &mVAO);
        glDeleteBuffers(1, &mVBO);
        glDeleteBuffers(1, &mEBO);
        glDeleteBuffers(1, &instanceVBO);
    }

private:
    std::vector<Vertex> mVertices;
    std::vector<unsigned int> mIndices;
    std::vector<Texture> mTextures;
    std::vector<glm::mat4> modelMatrices;
    unsigned int mAmount;
    ShaderType mType;

    void setupMesh(bool instanced)
    {
        glGenVertexArrays(1, &mVAO);
        glBindVertexArray(mVAO);

        glGenBuffers(1, &mVBO);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*mVertices.size(), &mVertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &mEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mIndices.size(), &mIndices[0], GL_STATIC_DRAW);
        
        setupAttribPointers();
        glBindVertexArray(0);
    }

    void setupAttribPointers()
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        switch (mType)
        {
        case CLR_SHADER:
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
            break;
        case CLR_NORMAL_SHADER:
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
            break;
        case TEX_SHADER:
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
            break;
        case TEX_NORMAL_SHADER:
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
            break;
        case INSTANCE_TEX_SHADER:
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

            modelMatrices = createAsteroidFieldMatrices(mAmount);
            glGenBuffers(1, &instanceVBO);
            glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
            glBufferData(GL_ARRAY_BUFFER, mAmount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
            glEnableVertexAttribArray(4);
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
            glEnableVertexAttribArray(5);
            glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
            glEnableVertexAttribArray(6);
            glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

            glVertexAttribDivisor(3, 1);
            glVertexAttribDivisor(4, 1);
            glVertexAttribDivisor(5, 1);
            glVertexAttribDivisor(6, 1);
            break;
        default:
            break;
        }
    }

    std::vector<glm::mat4> createAsteroidFieldMatrices(unsigned int amount)
    {
        std::vector<glm::mat4> modelMatrices;
        srand(glfwGetTime()); // initialize random seed	
        float radius = 150.0f;
        float offset = 25.0f;

        for (unsigned int i = 0; i < amount; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            float angle = i*1.0f / amount*360.0f;
            float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
            float x = sin(angle)*radius + displacement;
            displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
            float y = displacement * 0.4f;
            displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
            float z = cos(angle)*radius / 5.0f + displacement;
            model = glm::translate(model, glm::vec3(x, y, z));

            float rotAngle = (rand() % 360);
            model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

            float scale = (rand() % 20) / 100.0f + 0.05;
            model = glm::scale(model, glm::vec3(scale));

            modelMatrices.push_back(model);

        }

        return modelMatrices;
    }
};

#endif