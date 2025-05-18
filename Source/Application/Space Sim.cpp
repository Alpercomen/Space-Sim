#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>

#include <Application/Window/Window.h>
#include <Application/Shapes/Sphere/Sphere.h>
#include <Application/Utils/ShaderUtils/ShaderUtils.h>
#include <Application/Utils/SpaceUtils/SpaceUtils.h>
#include <Application/Constants/Constants.h>
#include <Application/Core/Engine/Engine.h>
#include <Application/Core/Input/Input.h>
#include "Application/Utils/ImGUIUtils/ImGUIUtils.h"

int main()
{
    GLFWwindow* window = Window::StartGLFW();

    if (!window)
        return -1;

    // Register input callbacks
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();

    ImGUIUtils::Initialize(window);

    glEnable(GL_DEPTH_TEST);

    GLuint shaderProgram = CreateShaderProgram(R"(D:\Documents\Projects\SS CMake\Source\Application\Shaders\shader.vert)", R"(D:\Documents\Projects\SS CMake\Source\Application\Shaders\shader.frag)");

    Engine engine(shaderProgram, window);
    engine.InitFBO();
    engine.Render(shaderProgram, window, camera);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}