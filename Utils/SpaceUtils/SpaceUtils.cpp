#pragma once

#include "SpaceUtils/SpaceUtils.h"
#include "Constants.h"

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

		Vector unitVector = Vector(dx, dy, dz).normal();
		float distance = unitVector.magnitude() * METER_PER_KILOMETER;

		float Gforce = (G * obj.circleDesc.mass * obj2.circleDesc.mass) / (distance * distance);
		float acc = Gforce / obj.circleDesc.mass;

		Acceleration attraction(acc * unitVector.x, acc * unitVector.y, acc * unitVector.z);

		obj.Accelerate(attraction);
	}
}