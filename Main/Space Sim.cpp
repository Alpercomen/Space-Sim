#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>

#include "Window.h"
#include "Sphere/Sphere.h"
#include "ShaderUtils/ShaderUtils.h"
#include "SpaceUtils/SpaceUtils.h"
#include "Constants.h"
#include "Engine/Engine.h"
#include "ImGUIUtils/ImGUIUtils.h"
#include "Input/Input.h"

int main()
{
    GLFWwindow* window = Window::StartGLFW();

    if (!window)
        return -1;

    // Register input callbacks
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, screenWidth, screenHeight);

    ImGUIUtils::Initialize(window);

    glEnable(GL_DEPTH_TEST);

    GLuint shaderProgram = CreateShaderProgram("Shaders/shader.vert", "Shaders/shader.frag");

    //Render
    Render(shaderProgram, window, screenWidth, screenHeight, camera);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}