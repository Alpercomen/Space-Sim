#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Velocity{
public:
	// CTOR
	Velocity()
	{
		world = glm::vec3();
		normalized = glm::vec3();
	}

	Velocity(glm::vec3 velocity, bool normal = false)
	{
		setVelocity(velocity, normal);
	}

	Velocity(double x, double y, double z, bool normal = false)
	{
		setX(x, normal);
		setY(y, normal);
		setZ(z, normal);
	}

	// Getters
	double getX(bool normal = false) { return normal ? normalized.x : world.x; }
	double getY(bool normal = false) { return normal ? normalized.y : world.y; }
	double getZ(bool normal = false) { return normal ? normalized.z : world.z; }

	// Setters
	void setVelocity(glm::vec3 velocity, bool normal = false)
	{
		if (normal)
		{
			world.x = velocity.x * METERS_PER_UNIT;
			world.y = velocity.y * METERS_PER_UNIT;
			world.z = velocity.z * METERS_PER_UNIT;
			
			normalized = velocity;
		}
		else
		{
			world = velocity;

			normalized.x = velocity.x / METERS_PER_UNIT;
			normalized.y = velocity.y / METERS_PER_UNIT;
			normalized.z = velocity.z / METERS_PER_UNIT;
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