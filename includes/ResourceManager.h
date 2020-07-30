#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <GL/gl.h>
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include<string>

#define SHADOW_WIDTH 1024
#define SHADOW_HEIGHT 1024

class ResourceManager
{
public:
    static uint32_t loadTexture(std::string path);
    static void createFramebuffer(uint32_t& fbo, uint32_t viewport_width, uint32_t viewport_height);
    static void createTextureAttachment(uint32_t fbo, uint32_t& colorTexture, uint32_t viewport_width, uint32_t viewport_height);
    static void createDepthTextureAttachment(uint32_t fbo, uint32_t& depthTexture, uint32_t viewport_width, uint32_t viewport_height);
    static void createDepthBufferAttachment(uint32_t fbo, uint32_t& rbo, uint32_t viewport_width, uint32_t viewport_height);
};

#endif