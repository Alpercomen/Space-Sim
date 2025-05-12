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

void Engine::DrawGUI(std::vector<Sphere>& objects, Camera& camera)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGUIUtils::InitDockableWindowSpace();
    ImVec2 textureSize = ImGUIUtils::DrawGameView(sceneColorTex);

    ImGUIUtils::DrawSimulationControl(objects, camera);
    ImGUIUtils::DrawSimulationInfo(objects, camera);

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
}

void Engine::InitFBO()
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

void Engine::ResizeFBO(int width, int height)
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

void Engine::Render(std::vector<Sphere>& objects, Camera& camera)
{
    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

    // Render loop
    while (!glfwWindowShouldClose(windowPtr))
    {
        glfwPollEvents();

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if (rightMouseButtonDown)
            process_keyboard_input(windowPtr, deltaTime, camera);

        glBindFramebuffer(GL_FRAMEBUFFER, sceneFBO);

        glViewport(0, 0, sceneTexWidth, sceneTexHeight);
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader);

        double aspectRatio = (float)sceneTexHeight == 0 ? 1280.0f / 720.0f : (float)sceneTexWidth / (float)sceneTexHeight;
        for (auto& object : objects)
        {
            Attract(object, objects);
            object.UpdatePos();
            object.Draw(camera, aspectRatio, shader);
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        DrawGUI(objects, camera);

        glfwSwapBuffers(windowPtr);
    }
}