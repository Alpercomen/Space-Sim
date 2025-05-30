#pragma once
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Application/Resource/Utils/SpaceUtils/SpaceUtils.h>
#include <Application/Resource/Components/Components.h>
#include <Application/Constants/Constants.h>


double GravitationalForce(double mu, double r) 
{
	return mu / (r * r);
}

double CalculateOrbitalVelocity(double otherMass, double r)
{
	return std::sqrt(G * otherMass / r) / METER_PER_KILOMETER;
}

void Attract(EntityID& objID)
{
	if (!ECS::Get().HasComponent<Rigidbody>(objID) || !ECS::Get().HasComponent<Position>(objID))
		return;

    auto& spheres = ECS::Get().GetAllComponents<Sphere>();
    auto sphereIDs = ECS::Get().GetAllComponentIDs<Sphere>();

	for (size_t i = 0; i < spheres.size(); ++i)
	{
        const EntityID& id = sphereIDs[i];
		if (objID == id)
			continue;

        if (!ECS::Get().HasComponent<Rigidbody>(id) || !ECS::Get().HasComponent<Position>(id) || !ECS::Get().HasComponent<Velocity>(id) || !ECS::Get().HasComponent<Acceleration>(id))
            continue;

        auto& objPos  = *ECS::Get().GetComponent<Position>(objID);
        auto& objRig  = *ECS::Get().GetComponent<Rigidbody>(objID);

		auto& obj2Pos  = *ECS::Get().GetComponent<Position>(id);
		auto& obj2Rig  = *ECS::Get().GetComponent<Rigidbody>(id);
		auto& obj2Vel  = *ECS::Get().GetComponent<Velocity>(id);
		auto& obj2Acc  = *ECS::Get().GetComponent<Acceleration>(id);

		double dx = objPos.GetWorld().x - obj2Pos.GetWorld().x;
		double dy = objPos.GetWorld().y - obj2Pos.GetWorld().y;
		double dz = objPos.GetWorld().z - obj2Pos.GetWorld().z;

		Math::Vec3d diff = glm::vec3(dx, dy, dz);
		float distance = glm::length(diff) * METER_PER_KILOMETER;
		Math::Vec3d unitVector = glm::normalize(diff);

		float Gforce = (G * objRig.mass * obj2Rig.mass) / (distance * distance);
		float acc = Gforce / obj2Rig.mass;

        Math::Vec3d accVec(acc * unitVector.x, acc * unitVector.y, acc * unitVector.z);
		Acceleration attraction(accVec);

		obj2Acc = attraction;
		obj2Vel.Accelerate(obj2Acc);
	}
}