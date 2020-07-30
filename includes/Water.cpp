#include "Water.h"
#include "ResourceManager.h"

Water::Vertex::Vertex(float x, float y, float z) :
    pos(x, y, z), normal(0.0f, 1.0f, 0.0f)
{
    
}

void Water::init(uint32_t programID)
{
    m_programID = programID;
    
    initFramebuffers();
    initGeometry();
}

void Water::initFramebuffers()
{
    ResourceManager::createFramebuffer(reflectFboID, FBO_WIDTH, FBO_HEIGHT);
    ResourceManager::createTextureAttachment(reflectFboID, reflectColorTextureID, FBO_WIDTH, FBO_HEIGHT);
    ResourceManager::createDepthBufferAttachment(reflectFboID, reflectRboID, FBO_WIDTH, FBO_WIDTH);

    ResourceManager::createFramebuffer(refractFboID, FBO_WIDTH, FBO_HEIGHT);
    ResourceManager::createTextureAttachment(refractFboID, refractColorTextureID, FBO_WIDTH, FBO_HEIGHT);
    ResourceManager::createDepthTextureAttachment(refractFboID, refractDepthTextureID, FBO_WIDTH, FBO_WIDTH);
}

void Water::initGeometry()
{
    vertices =
    {
        Vertex(0.0f, 0.0f, 0.0f),
        Vertex(0.0f, 0.0f, 1.0f),
        Vertex(1.0f, 0.0f, 1.0f),
        Vertex(1.0f, 0.0f, 0.0f),
    };

    indices =
    {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    glGenBuffers(1, &m_VBO);

    // Fill mesh buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    // Set mesh attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindVertexArray(0);

    float scaleFactor = 100.0f;
    world = glm::mat4(1.0f);
    world = glm::scale(world, glm::vec3(scaleFactor, 0.0f, scaleFactor));
    //world = MathHelper::scale(world, glm::vec3(scaleFactor, 0.0f, scaleFactor));
}

void Water::setReflectFBO()
{
    glBindFramebuffer(GL_FRAMEBUFFER, reflectFboID);
}

void Water::setRefractFBO()
{
    glBindFramebuffer(GL_FRAMEBUFFER, refractFboID);
}

void Water::update(glm::mat4 vp)
{
    wvp = vp * world;
}

void Water::draw()
{
    glUniformMatrix4fv(glGetUniformLocation(m_programID, "WVP"), 1, GL_FALSE, &wvp[0][0]);
    //ShaderManager::setMat4(m_programID, "WVP", wvp, false);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, reflectFboID);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, refractFboID);

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}