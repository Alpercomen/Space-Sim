#pragma once
#include "Camera/Camera.h"

class Engine {
public:
	Engine(GLuint shader, GLFWwindow* windowPtr)
	{
		this->shader = shader;
		this->windowPtr = windowPtr;
	}

	void InitFBO();
	void ResizeFBO(int width, int height);
	void Render(GLuint shader, GLFWwindow* windowPtr, Camera& camera);

private:
	GLuint sceneFBO = 0;
	GLuint sceneColorTex = 0;
	GLuint sceneDepthRBO = 0;

	GLuint shader;
	GLFWwindow* windowPtr;

	int sceneTexWidth = 1280;
	int sceneTexHeight = 720;
};
