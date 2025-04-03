#pragma once

#include "SpaceUtils.h"

#include "SpaceUtils.h"
#include "Constants.h"

double GravitationalForce(double mu, double r) 
{
	return mu / (r * r);
}

void Attract(Circle& obj, std::vector<Circle>& objects)
{
	for (auto& obj2 : objects)
	{
		if (&obj2 == &obj)
			continue;

		float dx = obj2.circleDesc.pos.getX() - obj.circleDesc.pos.getX();
		float dy = obj2.circleDesc.pos.getY() - obj.circleDesc.pos.getY();

		Vector unitVector = Vector(dx, dy, 0.0).normal();
		float distance = unitVector.magnitude() * METER_PER_KILOMETER;

		float Gforce = (G * obj.circleDesc.mass * obj2.circleDesc.mass) / (distance * distance);
		float acc1 = Gforce / obj.circleDesc.mass;

		Acceleration attraction(acc1 * unitVector.x, acc1 * unitVector.y, 0.0);

		obj.Accelerate(attraction);
	}
}