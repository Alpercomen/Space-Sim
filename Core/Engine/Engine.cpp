#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Engine.h"
#include "SpaceUtils/SpaceUtils.h"
#include "Constants.h"
#include "Sphere/Sphere.h"
#include "ImGUIUtils/ImGUIUtils.h"
#include "Input/Input.h"

float lastFrame = 0.0f;

void Render(GLuint shader, GLFWwindow* windowPtr, int screenWidth, int screenHeight, Camera& camera)
{
    SphereDesc moonDesc;
    moonDesc.name = "Moon";
    moonDesc.pos.setX(0.0);
    moonDesc.pos.setY(-100000.0);
    moonDesc.pos.setZ(0.0);
    moonDesc.radius.set(100000.0);
    moonDesc.res = 50;
    moonDesc.mass = 730000000000000000000.0; // Moon mass
    moonDesc.vel.setX(0.0);
    moonDesc.vel.setY(0.0);
    moonDesc.vel.setZ(0.0);

    Sphere moon(moonDesc);

    SphereDesc asteroidDesc;
    asteroidDesc.name = "Asteroid";
    asteroidDesc.pos.setX(250000.0);
    asteroidDesc.pos.setY(0.0);
    asteroidDesc.pos.setZ(0.0);
    asteroidDesc.radius.set(15000.0f);
    asteroidDesc.res = 50;
    asteroidDesc.mass = 73000.0;
    asteroidDesc.vel.setX(0);
    asteroidDesc.vel.setY(0.0);
    asteroidDesc.vel.setZ(100000.0);

    Sphere asteroid(asteroidDesc);

    std::vector<Sphere> objects;

    objects.push_back(moon);
    objects.push_back(asteroid);

    // Render loop
    while (!glfwWindowShouldClose(windowPtr))
    {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (rightMouseButtonDown)
            process_keyboard_input(windowPtr, deltaTime, camera);

        camera.Update(deltaTime);

        glUseProgram(shader);

        // TODO: Refactor this!
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)screenWidth / screenHeight, 1.0f, 1e10f);

        for (auto& object : objects)
        {
            Attract(object, objects);

            object.UpdatePos();
            object.Draw(view, projection, shader);
        }

        ImGUIUtils::DrawWindow(objects);

        glfwSwapBuffers(windowPtr);
    }
}