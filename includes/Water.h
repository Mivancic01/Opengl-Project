#ifndef WATER_H
#define WATER_H

#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <vector>

#define FBO_WIDTH 400
#define FBO_HEIGHT 400

class Water
{
public:
    void init(uint32_t programID);
    void update(glm::mat4 vp);
    void draw();

    void setReflectFBO();
    void setRefractFBO();

private:
    struct Vertex
    {
        Vertex(float x, float y, float z);

        glm::vec3 pos;
        glm::vec3 normal;
    };

    void initFramebuffers();
    void initGeometry();

    uint32_t m_VAO, m_VBO;
    uint32_t m_programID;

    uint32_t reflectFboID, reflectColorTextureID, reflectRboID;
    uint32_t refractFboID, refractColorTextureID, refractDepthTextureID;

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    glm::mat4 wvp, world;
};

#endif 