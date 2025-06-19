#pragma once
#include <vector>

#include <Application/Resource/Components/Components.h>
#include <Application/Resource/Camera/Camera.h>
#include <Application/Resource/Utils/ShaderUtils/ShaderUtils.h>

#include <Application/Core/Renderer/Renderer.h>

namespace Nyx 
{
	class Engine {
	public:
		Engine(void* windowPtr)
		{
			this->windowPtr = static_cast<GLFWwindow*>(windowPtr);

			InitFBO();
		}

		void InitFBO();
		void ResizeFBO(int width, int height);
		void Present(Scene& scene);

	private:
		Renderer m_Renderer;

		GLuint sceneFBO = 0;
		GLuint sceneColorTex = 0;
		GLuint sceneDepthRBO = 0;
		GLFWwindow* windowPtr;

		int sceneTexWidth = 1280;
		int sceneTexHeight = 720;
	};

}

