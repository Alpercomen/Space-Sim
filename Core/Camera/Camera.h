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
	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	// Euler Angles
	float Yaw;
	float Pitch;

	// For Smoothing
	float TargetYaw;
	float TargetPitch;

	// Camera Options
	float MovementSpeed;
	float MovementSpeedMultiplier;
	float MouseSensitivity;
	float RotationSmoothness;
	float Zoom;

	Camera(glm::vec3 position);

	glm::mat4 GetViewMatrix();
	void Update(float deltaTime);
	void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
	void ProcessMouseScroll(float yOffset);
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);

private:
	void updateCameraVectors();
};

