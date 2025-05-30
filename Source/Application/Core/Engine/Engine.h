#pragma once
#include <vector>

#include <Application/Resource/Sphere/Sphere.h>
#include <Application/Resource/Camera/Camera.h>
#include <Application/Resource/Utils/ShaderUtils/ShaderUtils.h>

namespace SpaceSim 
{
	class Engine {
	public:
		Engine(void* windowPtr)
		{
			this->windowPtr = static_cast<GLFWwindow*>(windowPtr);
			this->shader = CreateShaderProgram(
				R"(D:\Documents\Projects\Space-Sim\Source\Application\Shaders\shader.vert)",
				R"(D:\Documents\Projects\Space-Sim\Source\Application\Shaders\shader.frag)"
			);

			InitFBO();
		}

		void InitFBO();
		void ResizeFBO(int width, int height);
		void Render(std::vector<std::shared_ptr<Sphere>>& objects, void* windowPtr, Camera& camera);

	private:
		GLuint sceneFBO = 0;
		GLuint sceneColorTex = 0;
		GLuint sceneDepthRBO = 0;

		GLuint shader;
		GLFWwindow* windowPtr;

		int sceneTexWidth = 1280;
		int sceneTexHeight = 720;
	};

}

