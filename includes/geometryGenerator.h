#ifndef GEOMETRYGENERATOR_H
#define GEOMETRYGENERATOR_H

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <string>
#include <vector>

#include "mesh.h"

class GeometryGenerator
{
public:
    static Mesh* generateTriangle(ShaderType type, std::vector<Texture> &textures)
    {
        Vertex vertex[3];
        //Position
        vertex[0].setPos(glm::vec3(-0.5f, 0.5f, 0.0f));
        vertex[1].setPos(glm::vec3(-0.5f, -0.5f, 0.0f));
        vertex[2].setPos(glm::vec3(0.5f, -0.5f, 0.0f));

        //Color
        vertex[0].setColor(glm::vec4(0.2f, 0.4f, 0.9f, 1.0f));
        vertex[1].setColor(glm::vec4(0.6f, 0.2f, 0.4f, 1.0f));
        vertex[2].setColor(glm::vec4(0.0f, 0.7f, 0.1f, 1.0f));

        //Normal
        vertex[0].setNormal(glm::vec3(0.0f, 0.0f, 1.0f));
        vertex[1].setNormal(glm::vec3(0.0f, 0.0f, 1.0f));
        vertex[2].setNormal(glm::vec3(0.0f, 0.0f, 1.0f));

        //TexCoord
        vertex[0].setTexCoord(glm::vec2(0.0f, 1.0f));
        vertex[1].setTexCoord(glm::vec2(0.0f, 0.0f));
        vertex[2].setTexCoord(glm::vec2(1.0f, 0.0f));

        std::vector<Vertex> vertices;
        vertices.push_back(vertex[0]);
        vertices.push_back(vertex[1]);
        vertices.push_back(vertex[2]);

        std::vector<unsigned int> indices =
        {
            0, 1, 2,
        };

        Mesh* mesh = new Mesh(vertices, indices, textures, type);
        return mesh;
    }

    static Mesh* generateQuad(ShaderType type, std::vector<Texture> &textures)
    {
        Vertex vertex[4];
        //Position
        vertex[0].setPos(glm::vec3(-0.5f, 0.5f, 0.0f));
        vertex[1].setPos(glm::vec3(-0.5f, -0.5f, 0.0f));
        vertex[2].setPos(glm::vec3(0.5f, -0.5f, 0.0f));
        vertex[3].setPos(glm::vec3(0.5f, 0.5f, 0.0f));

        //Color
        vertex[0].setColor(glm::vec4(0.2f, 0.4f, 0.9f, 1.0f));
        vertex[1].setColor(glm::vec4(0.6f, 0.2f, 0.4f, 1.0f));
        vertex[2].setColor(glm::vec4(0.0f, 0.7f, 0.1f, 1.0f));
        vertex[3].setColor(glm::vec4(0.5f, 0.1f, 0.6f, 1.0f));

        //Normal
        vertex[0].setNormal(glm::vec3(0.0f, 0.0f, 1.0f));
        vertex[1].setNormal(glm::vec3(0.0f, 0.0f, 1.0f));
        vertex[2].setNormal(glm::vec3(0.0f, 0.0f, 1.0f));
        vertex[3].setNormal(glm::vec3(0.0f, 0.0f, 1.0f));

        //TexCoord
        vertex[0].setTexCoord(glm::vec2(0.0f, 1.0f));
        vertex[1].setTexCoord(glm::vec2(0.0f, 0.0f));
        vertex[2].setTexCoord(glm::vec2(1.0f, 0.0f));
        vertex[3].setTexCoord(glm::vec2(1.0f, 1.0f));

        std::vector<Vertex> vertices;
        vertices.push_back(vertex[0]);
        vertices.push_back(vertex[1]);
        vertices.push_back(vertex[2]);
        vertices.push_back(vertex[3]);

        std::vector<unsigned int> indices =
        {
            0, 1, 2,
            0, 2, 3,
        };

        Mesh* mesh = new Mesh(vertices, indices, textures, type);
        return mesh;
    }

    static Mesh* generatePlane(ShaderType type, std::vector<Texture> &textures)
    {
        Vertex vertex[4];
        //Position
        vertex[0].setPos(glm::vec3( 25.0f, -0.5f,  25.0f));
        vertex[1].setPos(glm::vec3(-25.0f, -0.5f,  25.0f));
        vertex[2].setPos(glm::vec3(-25.0f, -0.5f, -25.0f));
        vertex[3].setPos(glm::vec3( 25.0f, -0.5f, -25.0f));

        //Color
        vertex[0].setColor(glm::vec4(0.2f, 0.4f, 0.9f, 1.0f));
        vertex[1].setColor(glm::vec4(0.6f, 0.2f, 0.4f, 1.0f));
        vertex[2].setColor(glm::vec4(0.0f, 0.7f, 0.1f, 1.0f));
        vertex[3].setColor(glm::vec4(0.5f, 0.1f, 0.6f, 1.0f));

        //Normal
        vertex[0].setNormal(glm::vec3(0.0f, 1.0f, 0.0f));
        vertex[1].setNormal(glm::vec3(0.0f, 1.0f, 0.0f));
        vertex[2].setNormal(glm::vec3(0.0f, 1.0f, 0.0f));
        vertex[3].setNormal(glm::vec3(0.0f, 1.0f, 0.0f));

        //TexCoord
        vertex[0].setTexCoord(glm::vec2(25.0f, 0.0f));
        vertex[1].setTexCoord(glm::vec2(0.0f, 0.0f));
        vertex[2].setTexCoord(glm::vec2(0.0f, 25.0f));
        vertex[3].setTexCoord(glm::vec2(25.0f, 25.0f));

        std::vector<Vertex> vertices;
        vertices.push_back(vertex[0]);
        vertices.push_back(vertex[1]);
        vertices.push_back(vertex[2]);
        vertices.push_back(vertex[3]);

        std::vector<unsigned int> indices =
        {
            0, 1, 2,
            0, 2, 3,
        };

        Mesh* mesh = new Mesh(vertices, indices, textures, type);
        return mesh;
    }

    static Mesh* generateCube(ShaderType type, std::vector<Texture> &textures)
    {
        Vertex vertex[24];
        //Position
        vertex[0].setPos(glm::vec3(-1.0f, -1.0f, -1.0f));
        vertex[1].setPos(glm::vec3(1.0f, 1.0f, -1.0f));
        vertex[2].setPos(glm::vec3(1.0f, -1.0f, -1.0f));
        vertex[3].setPos(glm::vec3(-1.0f, 1.0f, -1.0f));

        vertex[4].setPos(glm::vec3(-1.0f, -1.0f, 1.0f));
        vertex[5].setPos(glm::vec3(1.0f, -1.0f, 1.0f));
        vertex[6].setPos(glm::vec3(1.0f, 1.0f, 1.0f));
        vertex[7].setPos(glm::vec3(-1.0f, 1.0f, 1.0f));

        vertex[8].setPos(glm::vec3(-1.0f, 1.0f, 1.0f));
        vertex[9].setPos(glm::vec3(-1.0f, 1.0f, -1.0f));
        vertex[10].setPos(glm::vec3(-1.0f, -1.0f, -1.0f));
        vertex[11].setPos(glm::vec3(-1.0f, -1.0f, 1.0f));

        vertex[12].setPos(glm::vec3(1.0f, 1.0f, 1.0f));
        vertex[13].setPos(glm::vec3(1.0f, -1.0f, -1.0f));
        vertex[14].setPos(glm::vec3(1.0f, 1.0f, -1.0f));
        vertex[15].setPos(glm::vec3(1.0f, -1.0f, 1.0f));

        vertex[16].setPos(glm::vec3(-1.0f, -1.0f, -1.0f));
        vertex[17].setPos(glm::vec3(1.0f, -1.0f, -1.0f));
        vertex[18].setPos(glm::vec3(1.0f, -1.0f, 1.0f));
        vertex[19].setPos(glm::vec3(-1.0f, -1.0f, 1.0f));

        vertex[20].setPos(glm::vec3(-1.0f, 1.0f, -1.0f));
        vertex[21].setPos(glm::vec3(1.0f, 1.0f, 1.0f));
        vertex[22].setPos(glm::vec3(1.0f, 1.0f, -1.0f));
        vertex[23].setPos(glm::vec3(-1.0f, 1.0f, 1.0f));

        //Color
        vertex[0].setColor(glm::vec4(0.5f, 0.3f, 0.3f, 1.0f));
        vertex[1].setColor(glm::vec4(0.3f, 0.1f, 0.3f, 1.0f));
        vertex[2].setColor(glm::vec4(0.0f, 0.3f, 0.3f, 1.0f));
        vertex[3].setColor(glm::vec4(0.3f, 1.0f, 1.0f, 1.0f));

        vertex[4].setColor(glm::vec4(0.1f, 0.5f, 0.3f, 1.0f));
        vertex[5].setColor(glm::vec4(0.1f, 0.8f, 0.1f, 1.0f));
        vertex[6].setColor(glm::vec4(0.5f, 0.3f, 0.5f, 1.0f));
        vertex[7].setColor(glm::vec4(0.8f, 0.8f, 0.3f, 1.0f));

        vertex[8].setColor(glm::vec4(0.3f, 0.3f, 1.0f, 1.0f));
        vertex[9].setColor(glm::vec4(1.0f, 0.5f, 0.5f, 1.0f));
        vertex[10].setColor(glm::vec4(1.0f, 1.0f, 0.3f, 1.0f));
        vertex[11].setColor(glm::vec4(0.5f, 0.3f, 0.8f, 1.0f));

        vertex[12].setColor(glm::vec4(0.1f, 0.3f, 1.0f, 1.0f));
        vertex[13].setColor(glm::vec4(0.5f, 0.8f, 0.5f, 1.0f));
        vertex[14].setColor(glm::vec4(0.3f, 0.5f, 0.1f, 1.0f));
        vertex[15].setColor(glm::vec4(0.0f, 0.5f, 0.3f, 1.0f));

        vertex[16].setColor(glm::vec4(0.5f, 0.3f, 0.8f, 1.0f));
        vertex[17].setColor(glm::vec4(0.1f, 0.5f, 1.0f, 1.0f));
        vertex[18].setColor(glm::vec4(0.0f, 0.3f, 0.1f, 1.0f));
        vertex[19].setColor(glm::vec4(1.0f, 0.8f, 0.5f, 1.0f));

        vertex[20].setColor(glm::vec4(0.5f, 0.3f, 0.3f, 1.0f));
        vertex[21].setColor(glm::vec4(0.1f, 1.0f, 0.5f, 1.0f));
        vertex[22].setColor(glm::vec4(0.3f, 0.0f, 0.8f, 1.0f));
        vertex[23].setColor(glm::vec4(0.5f, 0.8f, 0.3f, 1.0f));

        //Normal
        vertex[0].setNormal(glm::vec3(0.0f, 0.0f, -1.0f));
        vertex[1].setNormal(glm::vec3(0.0f, 0.0f, -1.0f));
        vertex[2].setNormal(glm::vec3(0.0f, 0.0f, -1.0f));
        vertex[3].setNormal(glm::vec3(0.0f, 0.0f, -1.0f));

        vertex[4].setNormal(glm::vec3(0.0f, 0.0f, 1.0f));
        vertex[5].setNormal(glm::vec3(0.0f, 0.0f, 1.0f));
        vertex[6].setNormal(glm::vec3(0.0f, 0.0f, 1.0f));
        vertex[7].setNormal(glm::vec3(0.0f, 0.0f, 1.0f));

        vertex[8].setNormal(glm::vec3(-1.0f, 0.0f, 0.0f));
        vertex[9].setNormal(glm::vec3(-1.0f, 0.0f, 0.0f));
        vertex[10].setNormal(glm::vec3(-1.0f, 0.0f, 0.0f));
        vertex[11].setNormal(glm::vec3(-1.0f, 0.0f, 0.0f));

        vertex[12].setNormal(glm::vec3(1.0f, 0.0f, 0.0f));
        vertex[13].setNormal(glm::vec3(1.0f, 0.0f, 0.0f));
        vertex[14].setNormal(glm::vec3(1.0f, 0.0f, 0.0f));
        vertex[15].setNormal(glm::vec3(1.0f, 0.0f, 0.0f));

        vertex[16].setNormal(glm::vec3(0.0f, -1.0f, 0.0f));
        vertex[17].setNormal(glm::vec3(0.0f, -1.0f, 0.0f));
        vertex[18].setNormal(glm::vec3(0.0f, -1.0f, 0.0f));
        vertex[19].setNormal(glm::vec3(0.0f, -1.0f, 0.0f));

        vertex[20].setNormal(glm::vec3(0.0f, 1.0f, 0.0f));
        vertex[21].setNormal(glm::vec3(0.0f, 1.0f, 0.0f));
        vertex[22].setNormal(glm::vec3(0.0f, 1.0f, 0.0f));
        vertex[23].setNormal(glm::vec3(0.0f, 1.0f, 0.0f));

        //TexCoord
        vertex[0].setTexCoord(glm::vec2(0.0f, 0.0f));
        vertex[1].setTexCoord(glm::vec2(1.0f, 1.0f));
        vertex[2].setTexCoord(glm::vec2(1.0f, 0.0f));
        vertex[3].setTexCoord(glm::vec2(0.0f, 1.0f));

        vertex[4].setTexCoord(glm::vec2(0.0f, 0.0f));
        vertex[5].setTexCoord(glm::vec2(1.0f, 0.0f));
        vertex[6].setTexCoord(glm::vec2(1.0f, 1.0f));
        vertex[7].setTexCoord(glm::vec2(0.0f, 1.0f));

        vertex[8].setTexCoord(glm::vec2(1.0f, 0.0f));
        vertex[9].setTexCoord(glm::vec2(1.0f, 1.0f));
        vertex[10].setTexCoord(glm::vec2(0.0f, 1.0f));
        vertex[11].setTexCoord(glm::vec2(0.0f, 0.0f));

        vertex[12].setTexCoord(glm::vec2(1.0f, 0.0f));
        vertex[13].setTexCoord(glm::vec2(0.0f, 1.0f));
        vertex[14].setTexCoord(glm::vec2(1.0f, 1.0f));
        vertex[15].setTexCoord(glm::vec2(0.0f, 0.0f));

        vertex[16].setTexCoord(glm::vec2(0.0f, 1.0f));
        vertex[17].setTexCoord(glm::vec2(1.0f, 1.0f));
        vertex[18].setTexCoord(glm::vec2(1.0f, 0.0f));
        vertex[19].setTexCoord(glm::vec2(0.0f, 0.0f));

        vertex[20].setTexCoord(glm::vec2(0.0f, 1.0f));
        vertex[21].setTexCoord(glm::vec2(1.0f, 0.0f));
        vertex[22].setTexCoord(glm::vec2(1.0f, 1.0f));
        vertex[23].setTexCoord(glm::vec2(0.0f, 0.0f));

        std::vector<Vertex> vertices;
        for (int i = 0; i < 24; i++)
            vertices.push_back(vertex[i]);

        std::vector<unsigned int> indices =
        {
            0, 1, 2, 1, 0, 3,
            4, 5, 6, 6, 7, 4,
            8, 9, 10, 10, 11, 8,
            12, 13, 14, 13, 12, 15,
            16, 17, 18, 18, 19, 16,
            20, 21, 22, 21, 20, 23,
        };

        Mesh* mesh = new Mesh(vertices, indices, textures, type);
        return mesh;
    }

    static Mesh* generateSphere(ShaderType type, std::vector<Texture> &textures)
    {
        std::vector<Vertex> vertices;
        float PI = 3.14, sectorCount = 20, stackCount = 10, radius = 2.0f;

        float x, y, z, xy;
        float sectorStep = 2 * PI / sectorCount;
        float stackStep = PI / stackCount;
        float sectorAngle, stackAngle;

        for (int i = 0; i <= stackCount; ++i)
        {
            stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
            xy = radius * cosf(stackAngle);             // r * cos(u)
            z = radius * sinf(stackAngle);              // r * sin(u)

                                                        // add (sectorCount+1) vertices per stack
                                                        // the first and last vertices have same position and normal, but different tex coords
            for (int j = 0; j <= sectorCount; ++j)
            {
                sectorAngle = j * sectorStep;           // starting from 0 to 2pi

                                                        // vertex position (x, y, z)
                x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
                y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
                Vertex vertex;
                vertex.setPos(glm::vec3(x, y, z));
                
                vertex.setColor(glm::vec4(glm::cos(stackAngle), glm::sin(stackAngle), glm::cos(stackAngle), 1.0f));
                vertices.push_back(vertex);
            }
        }

        std::vector<unsigned int> indices;
        int k1, k2;
        for (int i = 0; i < stackCount; ++i)
        {
            k1 = i * (sectorCount + 1);     // beginning of current stack
            k2 = k1 + sectorCount + 1;      // beginning of next stack

            for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
            {
                // 2 triangles per sector excluding first and last stacks
                // k1 => k2 => k1+1
                if (i != 0)
                {
                    indices.push_back(k1);
                    indices.push_back(k2);
                    indices.push_back(k1 + 1);
                }

                // k1+1 => k2 => k2+1
                if (i != (stackCount - 1))
                {
                    indices.push_back(k1 + 1);
                    indices.push_back(k2);
                    indices.push_back(k2 + 1);
                }
            }
        }

        Mesh* mesh = new Mesh(vertices, indices, textures, type);
        return mesh;
    }

    static Mesh* createSkybox(ShaderType type, std::vector<Texture> &textures)
    {
        Vertex vertex[24];
        vertex[0].setPos(glm::vec3(-1.0f,  1.0f, -1.0f));
        vertex[1].setPos(glm::vec3(-1.0f, -1.0f, -1.0f));
        vertex[2].setPos(glm::vec3( 1.0f, -1.0f, -1.0f));
        vertex[3].setPos(glm::vec3( 1.0f,  1.0f, -1.0f));

        vertex[4].setPos(glm::vec3(-1.0f, -1.0f,  1.0f));
        vertex[5].setPos(glm::vec3(-1.0f, -1.0f, -1.0f));
        vertex[6].setPos(glm::vec3(-1.0f,  1.0f, -1.0f));
        vertex[7].setPos(glm::vec3(-1.0f,  1.0f,  1.0f));

        vertex[8].setPos(glm::vec3( 1.0f, -1.0f, -1.0f));
        vertex[9].setPos(glm::vec3( 1.0f, -1.0f,  1.0f));
        vertex[10].setPos(glm::vec3(1.0f,  1.0f,  1.0f));
        vertex[11].setPos(glm::vec3(1.0f,  1.0f, -1.0f));

        vertex[12].setPos(glm::vec3(-1.0f,-1.0f,  1.0f));
        vertex[13].setPos(glm::vec3(-1.0f, 1.0f,  1.0f));
        vertex[14].setPos(glm::vec3( 1.0f, 1.0f,  1.0f));
        vertex[15].setPos(glm::vec3( 1.0f,-1.0f,  1.0f));

        vertex[16].setPos(glm::vec3(-1.0f, 1.0f, -1.0f));
        vertex[17].setPos(glm::vec3( 1.0f, 1.0f, -1.0f));
        vertex[18].setPos(glm::vec3( 1.0f, 1.0f,  1.0f));
        vertex[19].setPos(glm::vec3(-1.0f, 1.0f,  1.0f));

        vertex[20].setPos(glm::vec3(-1.0f,-1.0f, -1.0f));
        vertex[21].setPos(glm::vec3(-1.0f,-1.0f,  1.0f));
        vertex[22].setPos(glm::vec3( 1.0f,-1.0f, -1.0f));
        vertex[23].setPos(glm::vec3( 1.0f,-1.0f,  1.0f));

        std::vector<Vertex> vertices;
        for (int i = 0; i < 24; i++)
            vertices.push_back(vertex[i]);

        std::vector<unsigned int> indices =
        {
            0, 1, 2, 2, 3, 0,
            4, 5, 6, 6, 7, 4,
            8, 9, 10, 10, 11, 8,
            12, 13, 14, 14, 15, 12,
            16, 17, 18, 18, 19, 16,
            20, 21, 22, 22, 21, 23,
        };

        Mesh* mesh = new Mesh(vertices, indices, textures, type);
        return mesh;
    }

    static const std::vector<glm::mat4> createAsteroidFieldMatrices(unsigned int amount)
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
            float z = cos(angle)*radius/5.0f + displacement;
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