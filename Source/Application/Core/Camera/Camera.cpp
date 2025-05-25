#include "Camera.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <Application/Core/Core.h>
#include <Application/Window/Window.h>
#include <Application/Constants/Constants.h>
#include <Application/Core/Input/InputDispatcher.h>
#include <Application/Core/Input/InputEvent.h>
#include <Application/Core/Input/InputQueue.h>

using namespace SpaceSim;

Camera::Camera(glm::vec3 position)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
    MovementSpeed(METERS_PER_UNIT * 100),
    MovementSpeedMultiplier(3.5f),
    MouseSensitivity(0.1f),
    Zoom(45.0f),
    Yaw(-90.0f),
    Pitch(0.0f),
    WorldUp(glm::vec3(0.0f, 1.0f, 0.0f))
{
    Position = position;
    UpdateCameraVectors();

    InputHelper::ProcessMouseButtons();
    InputHelper::ProsessMouseMovement();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboardMovement(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;

    switch (direction) {
        case FORWARD:
            spdlog::info("Camera move forward input detected by {:03.6f} unit.", velocity);
            Position += Front * velocity;
            break;
        case BACKWARD:
            spdlog::info("Camera move backward input detected by {:03.6f} unit.", velocity);
            Position -= Front * velocity;
            break;
        case LEFT:
            spdlog::info("Camera move left input detected by {:03.6f} unit.", velocity);
            Position -= Right * velocity;
            break;
        case RIGHT:
            spdlog::info("Camera move right input detected by {:03.6f} unit.", velocity);
            Position += Right * velocity;
            break;
        case UP:
            spdlog::info("Camera move up input detected by {:03.6f} unit.", velocity);
            Position += WorldUp * velocity;
            break;
        case DOWN:
            spdlog::info("Camera move down input detected by {:03.6f} unit.", velocity);
            Position -= WorldUp * velocity;
            break;
    }   
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    spdlog::info("Camera movement = x:{:3.6f}, y:{:3.6f}", xoffset, yoffset);

    UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}
