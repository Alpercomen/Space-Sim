#pragma once
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Application/Window/Window.h>
#include <Application/Resource/Entities/Sphere/Sphere.h>
#include <Application/Resource/Utils/ShaderUtils/ShaderUtils.h>
#include <Application/Resource/Utils/SpaceUtils/SpaceUtils.h>
#include <Application/Constants/Constants.h>
#include <Application/Core/Engine/Engine.h>
#include <Application/Core/Input/InputDispatcher.h>

using namespace SpaceSim;

int main()
{
    BasicWindow window;
    Engine engine(window.GetHandle());

    Vector<SharedPtr<Sphere>> objects = CreateSolarSystem();

    window.Show();
    while(window.IsActive())
    {
        window.PollEvents();
        engine.Render(objects, window.GetHandle(), camera);
        window.SwapBuffers();
    }
    window.Hide();

    return 0;
}