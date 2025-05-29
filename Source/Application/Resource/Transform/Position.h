#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Application/Constants/Constants.h>

class Position {
public:
	// CTOR
	Position()
	{
		m_world = glm::vec3();
		m_normalized = glm::vec3();
	}

	Position(glm::vec3 position, bool normal = false)
	{
		normal ? SetNormal(position) : SetWorld(position);
	}

	~Position() = default;

	// Getters
	const glm::vec3& GetWorld() const { return m_world; }
	const glm::vec3& GetNormal() const { return m_normalized; }

	// Setters
	void SetWorld(const glm::vec3& position)
	{
		m_world = position;

		m_normalized.x = position.x / METERS_PER_UNIT;
		m_normalized.y = position.y / METERS_PER_UNIT;
		m_normalized.z = position.z / METERS_PER_UNIT;
	}

	void SetNormal(const glm::vec3& position)
	{
		m_world.x = position.x * METERS_PER_UNIT;
		m_world.y = position.y * METERS_PER_UNIT;
		m_world.z = position.z * METERS_PER_UNIT;

		m_normalized = position;
	}

	double distance3D(const Position& other) const
	{
		return glm::distance(this->GetWorld(), other.GetWorld());
	}

private:
	glm::vec3 m_world;
	glm::vec3 m_normalized;
};