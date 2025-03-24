#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>

#include "Window.h"
#include "Shapes.h"
#include "ShaderUtils.h"

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

    int res = 100;
    GLuint circleVAO = Shapes::CreateCircle(0.0f, 0.0f, 0.2f, res);

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(circleVAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, res + 2);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}