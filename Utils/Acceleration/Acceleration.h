#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Acceleration {
public:
	// CTOR
	Acceleration()
	{
		world = glm::vec3();
		normalized = glm::vec3();
	}

	Acceleration(glm::vec3 acceleration, bool normal = false)
	{
		setAcceleration(acceleration, normal);
	}
	
	Acceleration(double x, double y, double z, bool normal = false)
	{
		setX(x, normal);
		setY(y, normal);
		setZ(z, normal);
	}

	// Getters
	glm::vec3 getAcceleration(bool normal = false) { return normal ? normalized : world; }

	double getX(bool normal = false) { return normal ? normalized.x : world.x; }
	double getY(bool normal = false) { return normal ? normalized.y : world.y; }
	double getZ(bool normal = false) { return normal ? normalized.z : world.z; }

	// Setters
	void setAcceleration(glm::vec3 acceleration, bool normal = false)
	{
		if (normal)
		{
			world.x = acceleration.x * METERS_PER_UNIT;
			world.y = acceleration.y * METERS_PER_UNIT;
			world.z = acceleration.z * METERS_PER_UNIT;

			normalized = acceleration;
		}
		else
		{
			world = acceleration;

			normalized.x = acceleration.x / METERS_PER_UNIT;
			normalized.y = acceleration.y / METERS_PER_UNIT;
			normalized.z = acceleration.z / METERS_PER_UNIT;
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

private:
	glm::vec3 world;
	glm::vec3 normalized;
};