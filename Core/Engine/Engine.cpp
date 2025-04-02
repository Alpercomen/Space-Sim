#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>

#include "SpaceUtils.h"
#include "Constants.h"
#include "Circle.h"

void Render(GLuint shader, GLFWwindow* windowPtr, int screenWidth, int screenHeight)
{
    double r = EARTH_RADIUS_EQUATORAL;
    Acceleration acceleration(GravitationalForce(MU, r), -GravitationalForce(MU, r), 0.0);

    CircleDesc circleDesc;
    circleDesc.pos.setY(7.5);
    circleDesc.pos.setX(2.5);
    circleDesc.radius.set(1.0f);
    circleDesc.res = 50;

    CircleDesc circleDesc2;
    circleDesc2.pos.setY(7.5);
    circleDesc2.pos.setX(-2.5);
    circleDesc2.radius.set(1.0f);
    circleDesc2.res = 50;

    Circle circle1(circleDesc);
    Circle circle2(circleDesc2);

    std::vector<Circle> circles;

    circles.push_back(circle1);
    circles.push_back(circle2);

    // Render loop
    while (!glfwWindowShouldClose(windowPtr))
    {
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto& circle : circles)
        {
            circle.Accelerate(acceleration);
            circle.UpdatePos();
            circle.Draw();
        }

        glUseProgram(shader);

        glfwSwapBuffers(windowPtr);
    }
}