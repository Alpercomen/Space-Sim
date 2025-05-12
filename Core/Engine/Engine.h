#pragma once
#include "Camera/Camera.h"
#include "Sphere/Sphere.h"

#include "vector"

class Engine {
public:
    Engine(GLuint shader, GLFWwindow* windowPtr)
    {
        this->shader = shader;
        this->windowPtr = windowPtr;
    }

    void DrawGUI(std::vector<Sphere>& objects, Camera& camera);
    void InitFBO();
    void ResizeFBO(int width, int height);
    void Render(std::vector<Sphere>& objects, Camera& camera);

private:
    GLuint sceneFBO = 0;
    GLuint sceneColorTex = 0;
    GLuint sceneDepthRBO = 0;

    GLuint shader;
    GLFWwindow* windowPtr;

    int sceneTexWidth = 1280;
    int sceneTexHeight = 720;

};
