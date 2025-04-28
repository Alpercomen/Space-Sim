#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Acceleration {
public:

	Acceleration()
	{
		world = glm::vec3();
		normalized = glm::vec3();
	}
	
	Acceleration(double x, double y, double z, bool normalized = false)
	{
		setX(x, normalized);
		setY(y, normalized);
		setZ(z, normalized);
	}

	// Getters
	double getX(bool normal = false) { return normal ? normalized.x : world.x; }
	double getY(bool normal = false) { return normal ? normalized.y : world.y; }
	double getZ(bool normal = false) { return normal ? normalized.z : world.z; }

	// Setters
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

private:
	glm::vec3 world;
	glm::vec3 normalized;
};