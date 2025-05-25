//Camera.h
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera
{
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MovementSpeedMultiplier;
    float MouseSensitivity;
    float Zoom;

    Camera(glm::vec3 position);

    glm::mat4 GetViewMatrix();

    void ProcessKeyboardMovement(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

private:
    void UpdateCameraVectors();
};
