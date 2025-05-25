#pragma once
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Application/Window/Window.h>
#include <Application/Shapes/Sphere/Sphere.h>
#include <Application/Utils/ShaderUtils/ShaderUtils.h>
#include <Application/Utils/SpaceUtils/SpaceUtils.h>
#include <Application/Constants/Constants.h>
#include <Application/Core/Engine/Engine.h>
#include <Application/Core/Input/InputDispatcher.h>
#include <Application/Utils/ImGUIUtils/ImGUIUtils.h>

using namespace SpaceSim;

int main()
{
    BasicWindow window;

    ImGUIUtils::Initialize(window.GetHandle());

    Vector<SharedPtr<Sphere>> objects = CreateSolarSystem();

    GLuint shaderProgram = CreateShaderProgram(
        R"(D:\Documents\Projects\Space-Sim\Source\Application\Shaders\shader.vert)", 
        R"(D:\Documents\Projects\Space-Sim\Source\Application\Shaders\shader.frag)"
    );

    Engine engine(shaderProgram, window.GetHandle());
    engine.InitFBO();

    window.Show();
    while(window.IsActive())
    {
        window.PollEvents();
        engine.Render(objects, shaderProgram, window.GetHandle(), camera);
        window.SwapBuffers();
    }
    window.Hide();

    return 0;
}