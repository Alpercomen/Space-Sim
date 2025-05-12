#pragma once

#include "SpaceUtils/SpaceUtils.h"
#include "Constants.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

double GravitationalForce(double mu, double r) 
{
	return mu / (r * r);
}

double CalculateOrbitalVelocity(double otherMass, double r)
{
	return std::sqrt(G * otherMass / r);
}

void Attract(Sphere& obj, std::vector<Sphere>& objects)
{
	for (auto& obj2 : objects)
	{
		if (&obj2 == &obj)
			continue;

		glm::vec3 diff = obj2.circleDesc.getPosition() - obj.circleDesc.getPosition();
		float distance = glm::length(diff) * METER_PER_KILOMETER;
		glm::vec3 unitVector = glm::normalize(diff);

		float Gforce = (G * obj.circleDesc.mass * obj2.circleDesc.mass) / (distance * distance);
		float acc = Gforce / obj.circleDesc.mass;

		Acceleration attraction(acc * unitVector.x, acc * unitVector.y, acc * unitVector.z);

		obj.Accelerate(attraction);
	}
}

void PlaceInOrbit(SphereDesc& centerDesc, SphereDesc& orbittingDesc)
{
	double distance = glm::distance(orbittingDesc.getPosition(), centerDesc.getPosition());
	double orbitalSpeed = CalculateOrbitalVelocity(centerDesc.mass, distance);
	orbittingDesc.setVelocity(centerDesc.getVelocity() + glm::vec3(0.0, 0.0, orbitalSpeed));

	// Conservation of momentum
	double conservationSpeed = -orbitalSpeed * (orbittingDesc.mass / centerDesc.mass);
	centerDesc.setVelocity(orbittingDesc.getVelocity() + glm::vec3(0.0, 0.0, conservationSpeed));
}

void InitializeSun(SphereDesc& sunDesc)
{
	sunDesc.name = "Sun";
	sunDesc.res = 100;
	sunDesc.mass = SUN_MASS;
	sunDesc.radius.set(SUN_RADIUS / METER_PER_KILOMETER / 10);
	sunDesc.setPosition(glm::vec3(0.0f));
	sunDesc.topColor = glm::vec3(1.0, 1.0, 1.0);
	sunDesc.botColor = glm::vec3(1.0, 1.0, 1.0);
}

void InitializeEarth(SphereDesc& earthDesc)
{
	earthDesc.name = "Earth";
	earthDesc.res = 50;
	earthDesc.mass = EARTH_MASS;
	earthDesc.radius.set(EARTH_RADIUS_EQUATORAL / METER_PER_KILOMETER);
	earthDesc.setPosition(glm::vec3(AU / METER_PER_KILOMETER, 0.0, 0.0));
	earthDesc.topColor = glm::vec3(0.28, 0.56, 0.93);
	earthDesc.botColor = glm::vec3(0.11, 0.23, 0.37);
}

void InitializeMoon(SphereDesc& moonDesc)
{
	moonDesc.name = "Moon";
	moonDesc.res = 50;
	moonDesc.mass = MOON_MASS;
	moonDesc.radius.set(MOON_RADIUS / METER_PER_KILOMETER);
	moonDesc.setPosition(glm::vec3((EARTH_MOON_DISTANCE + AU) / METER_PER_KILOMETER, 0.0, 0.0));
	moonDesc.topColor = glm::vec3(0.89, 0.96, 0.96);
	moonDesc.botColor = glm::vec3(0.30, 0.41, 0.41);
}

void SetSolarSystem(std::vector<Sphere>& objects)
{
	SphereDesc sunDesc;
	SphereDesc earthDesc;
	SphereDesc moonDesc;

	InitializeSun(sunDesc);
	InitializeEarth(earthDesc);
	InitializeMoon(moonDesc);

	PlaceInOrbit(sunDesc, earthDesc);
	PlaceInOrbit(earthDesc, moonDesc);

	Sphere earth(earthDesc);
	Sphere moon(moonDesc);
	Sphere sun(sunDesc);

	objects.push_back(earth);
	objects.push_back(moon);
	objects.push_back(sun);
}
