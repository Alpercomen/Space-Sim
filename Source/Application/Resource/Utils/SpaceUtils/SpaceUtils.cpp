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

        const Position& pos1 = obj->GetPosition();
        const Position& pos2 = obj2->GetPosition();

		float dx = pos2.GetWorld().x - pos1.GetWorld().x;
		float dy = pos2.GetWorld().y - pos1.GetWorld().y;
		float dz = pos2.GetWorld().z - pos1.GetWorld().z;

		glm::vec3 diff = glm::vec3(dx, dy, dz);
		float distance = glm::length(diff) * METER_PER_KILOMETER;
		glm::vec3 unitVector = glm::normalize(diff);

		float Gforce = (G * obj->circleDesc.mass * obj2->circleDesc.mass) / (distance * distance);
		float acc = Gforce / obj->circleDesc.mass;

        glm::vec3 accVec(acc * unitVector.x, acc * unitVector.y, acc * unitVector.z);
		Acceleration attraction(accVec);

		obj->Accelerate(attraction);
	}
}

Vector<SharedPtr<Sphere>> CreateSolarSystem()
{
    Vector<SharedPtr<Sphere>> objects;

    SphereDesc earthDesc;
    SphereDesc moonDesc;
    
    earthDesc.res = 50;
    earthDesc.mass = 5.972e24; // Earth mass
    earthDesc.radius.SetWorld(12.5);
    earthDesc.vel.SetWorld(glm::vec3(0.0, 0.0, 0.0));
    earthDesc.topColor = glm::vec3(0.28, 0.56, 0.93);
    earthDesc.botColor = glm::vec3(0.11, 0.23, 0.37);

    moonDesc.res = 50;
    moonDesc.mass = 7.342e22; // Moon mass
    moonDesc.radius.SetWorld(3.0f);

    Position earthPos(glm::vec3(0.0f, 0.0f, 0.0f));
    Position moonPos(glm::vec3(384.400, 0.0, 0.0));

    double orbitalSpeed = CalculateOrbitalVelocity(earthDesc.mass, moonPos.distance3D(earthPos));
    moonDesc.vel.SetWorld(glm::vec3(0.0, 0.0, orbitalSpeed));

    // Conservation of momentum
    double earthSpeed = -orbitalSpeed * (moonDesc.mass / earthDesc.mass);
    earthDesc.vel.SetWorld(glm::vec3(0.0, 0.0, earthSpeed));

    moonDesc.topColor = glm::vec3(0.89, 0.96, 0.96);
    moonDesc.botColor = glm::vec3(0.30, 0.41, 0.41);

    std::shared_ptr<Sphere> earthPtr = std::make_shared<Sphere>(earthDesc);
    std::shared_ptr<Sphere> moonPtr = std::make_shared<Sphere>(moonDesc);

    earthPtr->SetName("Earth");
    earthPtr->SetPosition(earthPos);

    moonPtr->SetName("Moon");
    moonPtr->SetPosition(moonPos);

    objects.push_back(earthPtr);
    objects.push_back(moonPtr);

    return objects;
}