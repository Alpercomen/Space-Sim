#include <GLFW/glfw3.h>
#include "Input.h"
#include "Constants.h"

Camera camera(glm::vec3(0.0f, 0.0f, METERS_PER_UNIT));
bool firstMouse = true;
float lastX = 400.0f;
float lastY = 400.f;
bool rightMouseButtonDown = false;

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        if (!rightMouseButtonDown)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            rightMouseButtonDown = true;
        }
    }
    else
    {
        if (rightMouseButtonDown)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            rightMouseButtonDown = false;
            firstMouse = true; // Reset mouse movement
        }
        return;
    }

    if (firstMouse)
    {
        lastX = (float)xPos;
        lastY = (float)yPos;
        firstMouse = false;
    }

    float xOffset = (float)xPos - lastX;
    float yOffset = lastY - (float)yPos; // Reversed

    lastX = (float)xPos;
    lastY = (float)yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
    camera.ProcessMouseScroll((float)yOffset);
}

void process_keyboard_input(GLFWwindow* window, float deltaTime, Camera& camera)
{
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
        deltaTime *= camera.MovementSpeedMultiplier;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
}