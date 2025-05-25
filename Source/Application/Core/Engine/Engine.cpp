#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <Application/Core/Engine/Engine.h>
#include <Application/Utils/SpaceUtils/SpaceUtils.h>
#include <Application/Constants/Constants.h>
#include <Application/Utils/ImGUIUtils/ImGUIUtils.h>
#include <Application/Core/Input/InputDispatcher.h>

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

void Engine::Render(std::vector<std::shared_ptr<Sphere>>& objects, GLuint shader, void* windowPtr, Camera& camera)
{
    auto* glfwWindow = static_cast<GLFWwindow*>(windowPtr);

    int width, height;
    glfwGetFramebufferSize(glfwWindow, &width, &height);
    glBindFramebuffer(GL_FRAMEBUFFER, sceneFBO);

    glViewport(0, 0, sceneTexWidth, sceneTexHeight);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader);

    double aspectRatio = (float)sceneTexWidth / (float)sceneTexHeight;

    for (auto& object : objects)
    {
        Attract(object, objects);
        object->UpdatePos();
        object->Draw(camera, shader, aspectRatio);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    ImGUIUtils::DrawWindow(this, sceneColorTex, camera, objects);
}