#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>

#include "SpaceUtils.h"
#include "Constants.h"
#include "Circle.h"

void Render(GLuint shader, GLFWwindow* windowPtr, int screenWidth, int screenHeight)
{
    CircleDesc moonDesc;
    moonDesc.pos.setY(0.0);
    moonDesc.pos.setX(0.0);
    moonDesc.radius.set(7000.0f);
    moonDesc.res = 50;
    moonDesc.mass = 730000000000000000000.0; // Moon mass
    moonDesc.vel.setX(0.0);
    moonDesc.vel.setY(0.0);

    CircleDesc asteroidDesc;
    asteroidDesc.pos.setY(-50000.0);
    asteroidDesc.pos.setX(0.0);
    asteroidDesc.radius.set(1500.0f);
    asteroidDesc.res = 50;
    asteroidDesc.mass = 500000000.0;
    asteroidDesc.vel.setX(50000.0);
    asteroidDesc.vel.setY(0.0);

    Circle moon(moonDesc);
    Circle asteroid(asteroidDesc);

    std::vector<Circle> objects;

    objects.push_back(moon);
    objects.push_back(asteroid);

    // Render loop
    while (!glfwWindowShouldClose(windowPtr))
    {
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto& object : objects)
        {
            Attract(object, objects);

            object.UpdatePos();
            object.Draw();
        }

        glUseProgram(shader);

        glfwSwapBuffers(windowPtr);
    }
}