#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Application/Constants/Constants.h>

class Velocity {
public:
	// CTOR
	Velocity()
	{
		m_world = glm::vec3();
		m_normalized = glm::vec3();
	}

	Velocity(glm::vec3 velocity, bool normal = false)
	{
		normal ? SetNormal(velocity) : SetWorld(velocity);
	}

	~Velocity() = default;

	// Getters
	const glm::vec3& GetWorld() const { return m_world; }
	const glm::vec3& GetNormal() const { return m_normalized; }

	// Setters
	void SetWorld(const glm::vec3& velocity)
	{
		m_world = velocity;

		m_normalized.x = velocity.x / METERS_PER_UNIT;
		m_normalized.y = velocity.y / METERS_PER_UNIT;
		m_normalized.z = velocity.z / METERS_PER_UNIT;
	}

	void SetNormal(const glm::vec3& velocity)
	{
		m_world.x = velocity.x * METERS_PER_UNIT;
		m_world.y = velocity.y * METERS_PER_UNIT;
		m_world.z = velocity.z * METERS_PER_UNIT;

		m_normalized = velocity;
	}

private:
	glm::vec3 m_world;
	glm::vec3 m_normalized;
};