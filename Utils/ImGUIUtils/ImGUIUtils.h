#pragma once

#include "Circle.h"
#include <GLFW/glfw3.h>

namespace ImGUIUtils
{
	void Initialize(GLFWwindow* window);

	void DrawWindow(std::vector<Circle>& objects);
}


