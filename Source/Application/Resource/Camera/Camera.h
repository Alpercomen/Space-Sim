//Camera.h
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Application/Resource/EntityManager/EntityManager.h>

using namespace SpaceSim;

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

struct CameraDesc {
    glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 Right = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float Yaw = -90.0f;
    float Pitch = 0.0f;

    float MovementSpeed = METERS_PER_UNIT * 100;
    float MovementSpeedMultiplier = 3.5f;
    float MouseSensitivity = 0.1f;
    float Zoom = 45.0f;
};

class Camera
{
public:

    Camera();
    ~Camera() = default;

    glm::mat4 GetViewMatrix();

    const glm::vec3& GetFront() const { return m_cameraDesc.Front; }
    const glm::vec3& GetUp() const { return m_cameraDesc.Up; }
    const glm::vec3& GetRight() const { return m_cameraDesc.Right; }
    const glm::vec3& GetWorldUp() const { return m_cameraDesc.WorldUp; }

    const float GetYaw() const { return m_cameraDesc.Yaw; }
    const float GetPitch() const { return m_cameraDesc.Pitch; }

    const float GetMovementSpeed() const { return m_cameraDesc.MovementSpeed; }
    const float GetMovementSpeedMultiplier() const { return m_cameraDesc.MovementSpeedMultiplier; }
    const float GetMouseSensitivity() const { return m_cameraDesc.MouseSensitivity; }
    const float GetZoom() const { return m_cameraDesc.Zoom; }

    void SetFront(const glm::vec3& Front) { m_cameraDesc.Front = Front; }
    void SetUp(const glm::vec3& Up) { m_cameraDesc.Up = Up; }
    void SetRight(const glm::vec3& Right) { m_cameraDesc.Right = Right; }
    void SetWorldUp(const glm::vec3& WorldUp) { m_cameraDesc.WorldUp = WorldUp; }

    void SetYaw(const float32& Yaw) { m_cameraDesc.Yaw = Yaw; }
    void SetPitch(const float32& Pitch) { m_cameraDesc.Pitch = Pitch; }

    void SetMovementSpeed(const float32& MovementSpeed) { m_cameraDesc.MovementSpeed = MovementSpeed; }
    void SetMovementSpeedMultiplier(const float32& MovementSpeedMultiplier) { m_cameraDesc.MovementSpeedMultiplier = MovementSpeedMultiplier; }
    void SetMouseSensitivity(const float32& MouseSensitivity) { m_cameraDesc.MouseSensitivity = MouseSensitivity; }
    void SetZoom(const float32& Zoom) { m_cameraDesc.Zoom = Zoom; }

    void ProcessKeyboardMovement(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void UpdateCameraVectors();

private:
    CameraDesc m_cameraDesc;
};
