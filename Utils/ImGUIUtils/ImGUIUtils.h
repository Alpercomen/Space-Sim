#pragma once

#include "Sphere/Sphere.h"
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Camera/Camera.h"

namespace ImGUIUtils
{
	void Initialize(GLFWwindow* window);

	ImVec2 DrawWindow(Camera& camera, std::vector<Sphere>& objects, GLuint sceneTextureID);
}


