#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
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

GLuint sceneFBO = 0;
GLuint sceneColorTex = 0;
GLuint sceneDepthRBO = 0;

int sceneTexWidth = 1280;
int sceneTexHeight = 720;

void InitFBO()
{
    // Create texture
    glGenTextures(1, &sceneColorTex);
    glBindTexture(GL_TEXTURE_2D, sceneColorTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sceneTexWidth, sceneTexHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Create renderbuffer for depth
    glGenRenderbuffers(1, &sceneDepthRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, sceneDepthRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, sceneTexWidth, sceneTexHeight);

    // Create framebuffer
    glGenFramebuffers(1, &sceneFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, sceneFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, sceneColorTex, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, sceneDepthRBO);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cerr << "ERROR: Framebuffer not complete!\n";

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ResizeFBO(int width, int height)
{
    if (width == sceneTexWidth && height == sceneTexHeight)
        return;

    sceneTexWidth = width;
    sceneTexHeight = height;

    glDeleteFramebuffers(1, &sceneFBO);
    glDeleteTextures(1, &sceneColorTex);
    glDeleteRenderbuffers(1, &sceneDepthRBO);

    InitFBO(); // Recreate with new size
}

void Render(GLuint shader, GLFWwindow* windowPtr, Camera& camera)
{
    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

    SphereDesc earthDesc;
    earthDesc.name = "Earth";
    earthDesc.res = 50;
    earthDesc.mass = 5.972e24; // Earth mass
    earthDesc.radius.set(12500);
    earthDesc.pos.setPosition(glm::vec3(0.0, 0.0, 0.0));
    earthDesc.vel.setVelocity(glm::vec3(0.0, 0.0, 0.0));
    earthDesc.topColor = glm::vec3(0.28, 0.56, 0.93);
    earthDesc.botColor = glm::vec3(0.11, 0.23, 0.37);

    Sphere earth(earthDesc);

    SphereDesc moonDesc;
    moonDesc.name = "Moon";
    moonDesc.res = 50;
    moonDesc.mass = 7.342e22; // Moon mass
    moonDesc.radius.set(3000.0f);
    moonDesc.pos.setPosition(glm::vec3(384400.0, 0.0, 0.0));
    double orbitalSpeed = CalculateOrbitalVelocity(earthDesc.mass, moonDesc.pos.distance3D(earthDesc.pos.getPosition()));

    moonDesc.vel.setVelocity(glm::vec3(0.0, 0.0, orbitalSpeed));
    moonDesc.topColor = glm::vec3(0.89, 0.96, 0.96);
    moonDesc.botColor = glm::vec3(0.30, 0.41, 0.41);

    Sphere moon(moonDesc);

    std::vector<Sphere> objects;

    objects.push_back(earth);
    objects.push_back(moon);

    // Render loop
    while (!glfwWindowShouldClose(windowPtr))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();

        if (rightMouseButtonDown)
            process_keyboard_input(windowPtr, deltaTime, camera);

        int width, height;
        glfwGetFramebufferSize(windowPtr, &width, &height);
        glBindFramebuffer(GL_FRAMEBUFFER, sceneFBO);

        glViewport(0, 0, sceneTexWidth, sceneTexHeight);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader);

        for (auto& object : objects)
        {
            Attract(object, objects);
            object.UpdatePos();
            object.Draw(camera, shader);
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImVec2 textureSize = ImGUIUtils::DrawWindow(camera, objects, sceneColorTex);
        ResizeFBO((int)textureSize.x, (int)textureSize.y);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup);
        }

        glfwSwapBuffers(windowPtr);
    }
}