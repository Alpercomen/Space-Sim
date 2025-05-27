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
		SetPosition(position, normal);
	}

	Position(double x, double y, double z, bool normal = false)
	{
		SetX(x, normal);
		SetY(y, normal);
		SetZ(z, normal);
	}

	// Getters
	glm::vec3 GetPosition(bool normal = false) { return normal ? m_normalized : m_world; }

	double GetX(bool normal = false) { return normal ? m_normalized.x : m_world.x; }
	double GetY(bool normal = false) { return normal ? m_normalized.y : m_world.y; }
	double GetZ(bool normal = false) { return normal ? m_normalized.z : m_world.z; }

	// Setters
	void SetPosition(const glm::vec3& position, bool normal = false)
	{
		if (normal)
		{
			m_world.x = position.x * METERS_PER_UNIT;
			m_world.y = position.y * METERS_PER_UNIT;
			m_world.z = position.z * METERS_PER_UNIT;

			m_normalized = position;
		}
		else
		{
			m_world = position;

			m_normalized.x = position.x / METERS_PER_UNIT;
			m_normalized.y = position.y / METERS_PER_UNIT;
			m_normalized.z = position.z / METERS_PER_UNIT;
		}
	}

	void SetX(double x, bool normal = false)
	{
		if (normal)
		{
			m_world.x = x * METERS_PER_UNIT;
			m_normalized.x = x;
		}
		else
		{
			m_world.x = x;
			m_normalized.x = x / METERS_PER_UNIT;
		}
	}

	void SetY(double y, bool normal = false)
	{
		if (normal)
		{
			m_world.y = y * METERS_PER_UNIT;
			m_normalized.y = y;
		}
		else
		{
			m_world.y = y;
			m_normalized.y = y / METERS_PER_UNIT;
		}
	}

	void SetZ(double z, bool normal = false)
	{
		if (normal)
		{
			m_world.z = z * METERS_PER_UNIT;
			m_normalized.z = z;
		}
		else
		{
			m_world.z = z;
			m_normalized.z = z / METERS_PER_UNIT;
		}
	}

	double distance3D(const Position& other) const
	{
		double dx = this->m_world.x - other.m_world.x;
		double dy = this->m_world.y - other.m_world.y;
		double dz = this->m_world.z - other.m_world.z;

		return std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
	}

private:
	glm::vec3 m_world;
	glm::vec3 m_normalized;
};