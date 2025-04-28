#pragma once

#include "SpaceUtils/SpaceUtils.h"
#include "Constants.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

double GravitationalForce(double mu, double r) 
{
	return mu / (r * r);
}

void Attract(Sphere& obj, std::vector<Sphere>& objects)
{
	for (auto& obj2 : objects)
	{
		if (&obj2 == &obj)
			continue;

		float dx = obj2.circleDesc.pos.getX() - obj.circleDesc.pos.getX();
		float dy = obj2.circleDesc.pos.getY() - obj.circleDesc.pos.getY();
		float dz = obj2.circleDesc.pos.getZ() - obj.circleDesc.pos.getZ();

		glm::vec3 unitVector = glm::normalize(glm::vec3(dx, dy, dz));
		float distance = glm::length(unitVector) * METER_PER_KILOMETER;

		float Gforce = (G * obj.circleDesc.mass * obj2.circleDesc.mass) / (distance * distance);
		float acc = Gforce / obj.circleDesc.mass;

		Acceleration attraction(acc * unitVector.x, acc * unitVector.y, acc * unitVector.z);

		obj.Accelerate(attraction);
	}
}