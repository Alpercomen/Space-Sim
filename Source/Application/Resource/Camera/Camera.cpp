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

Camera::Camera(const Position& position)
{
    SetFront(glm::vec3(0.0f, 0.0f, -1.0f));
    SetMovementSpeed(METERS_PER_UNIT * 100);
    SetMovementSpeedMultiplier(3.5f);
    SetMouseSensitivity(0.1f);
    SetZoom(45.0f);
    SetYaw(-90.0f);
    SetPitch(0.0f);
    SetWorldUp(glm::vec3(0.0f, 1.0f, 0.0f));

    SetPosition(position);
    SetName("Camera");

    UpdateCameraVectors();

    InputHelper::ProcessMouseButtons();
    InputHelper::ProcessMouseMovement();
}

Camera::Camera(const Position& position, const String& name, const CameraDesc& cameraDesc)
{
    SetFront(cameraDesc.Front);
    SetMovementSpeed(cameraDesc.MovementSpeed);
    SetMovementSpeedMultiplier(cameraDesc.MovementSpeedMultiplier);
    SetMouseSensitivity(cameraDesc.MouseSensitivity);
    SetZoom(cameraDesc.Zoom);
    SetYaw(cameraDesc.Yaw);
    SetPitch(cameraDesc.Pitch);
    SetWorldUp(cameraDesc.WorldUp);

    SetPosition(position);
    SetName(name);

    UpdateCameraVectors();

    InputHelper::ProcessMouseButtons();
    InputHelper::ProcessMouseMovement();
}

glm::mat4 Camera::GetViewMatrix()
{
    Position pos = GetPosition();
    return glm::lookAt(pos.GetWorld(), pos.GetWorld() + GetFront(), GetUp());
}

void Camera::ProcessKeyboardMovement(Camera_Movement direction, float deltaTime)
{
    float velocity = GetMovementSpeed() * deltaTime;
    Position pos = GetPosition();

    switch (direction) {
        case FORWARD:
            spdlog::info("{} move forward input detected by {:03.6f} unit.", GetName(), velocity);
            pos.SetWorld(pos.GetWorld() + GetFront() * velocity);
            break;
        case BACKWARD:
            spdlog::info("{} move backward input detected by {:03.6f} unit.", GetName(), velocity);
            pos.SetWorld(pos.GetWorld() - GetFront() * velocity);
            break;
        case RIGHT:
            spdlog::info("{} move right input detected by {:03.6f} unit.", GetName(), velocity);
            pos.SetWorld(pos.GetWorld() + GetRight() * velocity);
            break;
        case LEFT:
            spdlog::info("{} move left input detected by {:03.6f} unit.", GetName(), velocity);
            pos.SetWorld(pos.GetWorld() - GetRight() * velocity);
            break;
        case UP:
            spdlog::info("{} move up input detected by {:03.6f} unit.", GetName(), velocity);
            pos.SetWorld(pos.GetWorld() + GetWorldUp() * velocity);
            break;
        case DOWN:
            spdlog::info("{} move down input detected by {:03.6f} unit.", GetName(), velocity);
            pos.SetWorld(pos.GetWorld() - GetWorldUp() * velocity);
            break;
    }

    SetPosition(pos);
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= GetMouseSensitivity();
    yoffset *= GetMouseSensitivity();

    SetYaw(GetYaw() + xoffset);
    SetPitch(GetPitch() + yoffset);

    if (constrainPitch)
    {
        if (GetPitch() > 89.0f)
            SetPitch(89.0f);
        if (GetPitch() < -89.0f)
            SetPitch(-89.0f);
    }

    spdlog::info("Camera movement = x:{:3.6f}, y:{:3.6f}", xoffset, yoffset);

    UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(GetYaw())) * cos(glm::radians(GetPitch()));
    front.y = sin(glm::radians(GetPitch()));
    front.z = sin(glm::radians(GetYaw())) * cos(glm::radians(GetPitch()));
    SetFront(glm::normalize(front));

    SetRight(glm::normalize(glm::cross(GetFront(), GetWorldUp())));
    SetUp(glm::normalize(glm::cross(GetRight(), GetFront())));
}
