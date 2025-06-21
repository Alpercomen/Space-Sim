#pragma once

#include <Application/Resource/Camera/Camera.h>
#include <Application/Core/Engine/Engine.h>
#include <Application/Resource/Components/Components.h>

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

using namespace Nyx;

namespace ImGUIUtils
{
	void Initialize(void* window);

	void InitDockableWindow();

	ImVec2 DrawGameWindow(GLuint sceneTextureID);

	void DrawSimulationInfo();

	void DrawSimulationControl();

	void DrawWindow(Engine* enginePtr, Scene* scenePtr);
}


