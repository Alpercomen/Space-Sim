#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>

#include "Window.h"
#include "Shapes.h"

int main()
{
    GLFWwindow* window = Window::StartGLFW();

    if (!window)
        return -1;

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    glViewport(0, 0, screenWidth, screenHeight);

    float centerX = 0.0f;  // OpenGL Normalized coordinate system
    float centerY = 0.0f;
    float radius = 0.2f;  // Normalized radius
    int res = 100;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(1.0f, 1.0f, 1.0f); // Set color to white

        Shapes::CreateCircle(centerX, centerY, radius, res);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}