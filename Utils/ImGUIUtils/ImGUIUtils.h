#pragma once

#include "Sphere/Sphere.h"
#include "Camera/Camera.h"
#include "Engine/Engine.h"

#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


namespace ImGUIUtils
{
	void Initialize(GLFWwindow* window);

	void InitDockableWindow();

	ImVec2 DrawGameWindow(GLuint sceneTextureID);

	void DrawSimulationInfo(Camera& camera, std::vector<Sphere>& objects);

	void DrawSimulationControl(Camera& camera, std::vector<Sphere>& objects);

	void DrawWindow(Engine* engine, GLuint sceneTextureID, Camera& camera, std::vector<Sphere>& objects);
}


