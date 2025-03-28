#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>

#include "Window.h"
#include "Circle.h"
#include "ShaderUtils.h"
#include "SpaceUtils.h"
#include "Constants.h"
#include "Engine.h"

int main()
{
    GLFWwindow* window = Window::StartGLFW();

    if (!window)
        return -1;

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, screenWidth, screenHeight);

    GLuint shaderProgram = CreateShaderProgram("Shaders/shader.vert", "Shaders/shader.frag");

    //Render
    Render(shaderProgram, window);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}