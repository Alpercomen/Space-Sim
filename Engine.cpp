#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>

#include "SpaceUtils.h"
#include "Constants.h"
#include "Circle.h"

void Render(GLuint shader, GLFWwindow* windowPtr)
{
    // World-space variables (meters)
    double posY_world = 7.5;
    double velY_world = 0.0;

    CircleDesc circleDesc;
    circleDesc.posX = 0.0f;
    circleDesc.radius = 0.1f;
    circleDesc.res = 50;

    // Render loop
    while (!glfwWindowShouldClose(windowPtr))
    {
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Physics update in meters
        double r = EARTH_RADIUS_EQUATORAL;
        double acc = -GravitationalForce(MU, r); // m/s²
        velY_world += acc * DELTA_TIME;
        posY_world += velY_world * DELTA_TIME;

        // Convert to normalized OpenGL space
        circleDesc.posY = posY_world / METERS_PER_UNIT;

        // Use core pipeline
        glUseProgram(shader);
        GLuint circleVAO = CreateCircle(circleDesc);
        glBindVertexArray(circleVAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, circleDesc.res + 2);

        glfwSwapBuffers(windowPtr);
    }
}