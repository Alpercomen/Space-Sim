#pragma once
#include <iostream>

#include <Application/Resource/Utils/SpaceUtils/SpaceUtils.h>
#include <Application/Constants/Constants.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

double GravitationalForce(double mu, double r) 
{
	return mu / (r * r);
}

double CalculateOrbitalVelocity(double otherMass, double r)
{
	return std::sqrt(G * otherMass / r) / METER_PER_KILOMETER;
}

void Attract(SharedPtr<Sphere>& obj, Vector<SharedPtr<Sphere>>& objects)
{
	for (auto& obj2 : objects)
	{
		if (&obj == &obj2)
			continue;

		float dx = obj2->circleDesc.pos.GetX() - obj->circleDesc.pos.GetX();
		float dy = obj2->circleDesc.pos.GetY() - obj->circleDesc.pos.GetY();
		float dz = obj2->circleDesc.pos.GetZ() - obj->circleDesc.pos.GetZ();

		glm::vec3 diff = glm::vec3(dx, dy, dz);
		float distance = glm::length(diff) * METER_PER_KILOMETER;
		glm::vec3 unitVector = glm::normalize(diff);

		float Gforce = (G * obj->circleDesc.mass * obj2->circleDesc.mass) / (distance * distance);
		float acc = Gforce / obj->circleDesc.mass;

		Acceleration attraction(acc * unitVector.x, acc * unitVector.y, acc * unitVector.z);

		obj->Accelerate(attraction);
	}
}

Vector<SharedPtr<Sphere>> CreateSolarSystem()
{
    Vector<SharedPtr<Sphere>> objects;

    SphereDesc earthDesc;
    earthDesc.name = "Earth";
    earthDesc.res = 50;
    earthDesc.mass = 5.972e24; // Earth mass
    earthDesc.radius.set(12.5);
    earthDesc.pos.SetPosition(glm::vec3(0.0, 0.0, 0.0));
    earthDesc.vel.setVelocity(glm::vec3(0.0, 0.0, 0.0));
    earthDesc.topColor = glm::vec3(0.28, 0.56, 0.93);
    earthDesc.botColor = glm::vec3(0.11, 0.23, 0.37);

    SphereDesc moonDesc;
    moonDesc.name = "Moon";
    moonDesc.res = 50;
    moonDesc.mass = 7.342e22; // Moon mass
    moonDesc.radius.set(3.0f);
    moonDesc.pos.SetPosition(glm::vec3(384.400, 0.0, 0.0));

    double orbitalSpeed = CalculateOrbitalVelocity(earthDesc.mass, moonDesc.pos.distance3D(earthDesc.pos.GetPosition()));
    moonDesc.vel.setVelocity(glm::vec3(0.0, 0.0, orbitalSpeed));

    // Conservation of momentum
    double earthSpeed = -orbitalSpeed * (moonDesc.mass / earthDesc.mass);
    earthDesc.vel.setVelocity(glm::vec3(0.0, 0.0, earthSpeed));

    moonDesc.topColor = glm::vec3(0.89, 0.96, 0.96);
    moonDesc.botColor = glm::vec3(0.30, 0.41, 0.41);

    objects.push_back(std::make_shared<Sphere>(earthDesc));
    objects.push_back(std::make_shared<Sphere>(moonDesc));

    return objects;
}