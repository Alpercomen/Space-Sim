#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Constants.h"

class Position {
public:
	// CTOR
	Position()
	{
		world = glm::vec3();
		normalized = glm::vec3();
	}

	Position(glm::vec3 position, bool normal = false)
	{
		setPosition(position, normal);
	}

	Position(double x, double y, double z, bool normal = false)
	{
		setX(x, normal);
		setY(y, normal);
		setZ(z, normal);
	}

	// Getters
	glm::vec3 getPosition(bool normal = false) { return normal ? normalized : world; }

	double getX(bool normal = false) { return normal ? normalized.x : world.x; }
	double getY(bool normal = false) { return normal ? normalized.y : world.y; }
	double getZ(bool normal = false) { return normal ? normalized.z : world.z; }

	// Setters
	void setPosition(glm::vec3 position, bool normal = false)
	{
		if (normal)
		{
			world.x = position.x * METERS_PER_UNIT;
			world.y = position.y * METERS_PER_UNIT;
			world.z = position.z * METERS_PER_UNIT;

			normalized = position;
		}
		else
		{
			world = position;

			normalized.x = position.x / METERS_PER_UNIT;
			normalized.y = position.y / METERS_PER_UNIT;
			normalized.z = position.z / METERS_PER_UNIT;
		}
	}

	void setX(double x, bool normal = false)
	{
		if (normal)
		{
			world.x = x * METERS_PER_UNIT;
			normalized.x = x;
		}
		else
		{
			world.x = x;
			normalized.x = x / METERS_PER_UNIT;
		}
	}

	void setY(double y, bool normal = false)
	{
		if (normal)
		{
			world.y = y * METERS_PER_UNIT;
			normalized.y = y;
		}
		else
		{
			world.y = y;
			normalized.y = y / METERS_PER_UNIT;
		}
	}

	void setZ(double z, bool normal = false)
	{
		if (normal)
		{
			world.z = z * METERS_PER_UNIT;
			normalized.z = z;
		}
		else
		{
			world.z = z;
			normalized.z = z / METERS_PER_UNIT;
		}
	}

	double distance3D(const Position& other) const
	{
		double dx = this->world.x - other.world.x;
		double dy = this->world.y - other.world.y;
		double dz = this->world.z - other.world.z;

		return std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
	}

private:
	glm::vec3 world;
	glm::vec3 normalized;
};