#pragma once
#include "Camera/Camera.h"

extern GLuint sceneFBO;
extern GLuint sceneColorTex;
extern GLuint sceneDepthRBO;

extern int sceneTexWidth;
extern int sceneTexHeight;

void InitFBO();
void ResizeFBO(int width, int height);
void Render(GLuint shader, GLFWwindow* windowPtr, Camera& camera);