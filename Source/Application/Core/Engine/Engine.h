#pragma once
#include <vector>

#include <Application/Shapes/Sphere/Sphere.h>
#include <Application/Core/Camera/Camera.h>

class Engine {
public:
	Engine(GLuint shader, void* windowPtr)
	{
		this->shader = shader;
		this->windowPtr = static_cast<GLFWwindow*>(windowPtr);
	}

	void InitFBO();
	void ResizeFBO(int width, int height);
	void Render(std::vector<std::shared_ptr<Sphere>>& objects, GLuint shader, void* windowPtr, Camera& camera);

private:
	GLuint sceneFBO = 0;
	GLuint sceneColorTex = 0;
	GLuint sceneDepthRBO = 0;

	GLuint shader;
	GLFWwindow* windowPtr;

	int sceneTexWidth = 1280;
	int sceneTexHeight = 720;
};
