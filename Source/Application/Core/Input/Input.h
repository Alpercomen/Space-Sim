#pragma once
#include <Application/Core/Camera/Camera.h>

extern Camera camera;
extern bool firstMouse;
extern float lastX;
extern float lastY;
extern bool rightMouseButtonDown;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);

void process_keyboard_input(GLFWwindow* window, float deltaTime, Camera& camera);

