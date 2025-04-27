#pragma once

#include "Sphere/Sphere.h"
#include <GLFW/glfw3.h>

namespace ImGUIUtils
{
	void Initialize(GLFWwindow* window);

	void DrawWindow(std::vector<Sphere>& objects);
}


