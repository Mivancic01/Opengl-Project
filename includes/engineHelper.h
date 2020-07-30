#ifndef ENGINEHELPER_H
#define ENGINEHELPER_H

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "camera.h"
#include "stb_image.h"

#include <iostream>

namespace EngineNamespace
{
    extern Camera camera;
    extern bool firstMouse;
    extern float mouseLastXPos, mouseLastYPos;
    extern unsigned int WIDTH, HEIGHT;

    unsigned int createTex(const char* texPath);
    unsigned int createCubeMap(std::vector<std::string> faces);
    void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);
    GLFWwindow* initWindow();
};

#endif