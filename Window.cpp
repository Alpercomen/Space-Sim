#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"

GLFWwindow* Window::StartGLFW()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW..." << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Space Sim", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window..." << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window); // Ensure OpenGL context is active before returning
    return window;
}

