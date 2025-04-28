#include <GLFW/glfw3.h>
#include "Input.h"
#include "Constants.h"

Camera camera(glm::vec3(0.0f, 0.0f, -100000.0f));
bool firstMouse = true;
float lastX = 400.0f;
float lastY = 400.f;
bool rightMouseButtonDown = false;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            rightMouseButtonDown = true;
            firstMouse = true;
        }
        else if (action == GLFW_RELEASE)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            rightMouseButtonDown = false;
        }
    }
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
    if (!rightMouseButtonDown)
        return;

    if (firstMouse)
    {
        lastX = (float)xPos;
        lastY = (float)yPos;
        firstMouse = false;
    }

    float xoffset = (float)xPos - lastX;
    float yoffset = lastY - (float)yPos; // reversed y

    lastX = (float)xPos;
    lastY = (float)yPos;

    camera.ProcessMouseMovement(xoffset, yoffset);
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