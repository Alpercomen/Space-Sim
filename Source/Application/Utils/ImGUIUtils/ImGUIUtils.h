#pragma once

#include <Application/Shapes/Sphere/Sphere.h>
#include <Application/Core/Camera/Camera.h>
#include <Application/Core/Engine/Engine.h>

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>


namespace ImGUIUtils
{
	void Initialize(void* window);

	void InitDockableWindow();

	ImVec2 DrawGameWindow(GLuint sceneTextureID);

	void DrawSimulationInfo(Camera& camera, std::vector<std::shared_ptr<Sphere>>& objects);

	void DrawSimulationControl(Camera& camera, std::vector<std::shared_ptr<Sphere>>& objects);

	void DrawWindow(Engine* engine, GLuint sceneTextureID, Camera& camera, std::vector<std::shared_ptr<Sphere>>& objectss);
}


