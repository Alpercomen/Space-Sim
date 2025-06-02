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

void InitializeCircularOrbit(EntityID satelliteID, EntityID attractorID) {
    // Ensure required components
    if (!ECS::Get().HasComponent<Position>(satelliteID) ||
        !ECS::Get().HasComponent<Position>(attractorID) ||
        !ECS::Get().HasComponent<Rigidbody>(satelliteID) ||
        !ECS::Get().HasComponent<Rigidbody>(attractorID)) 
    {
        spdlog::error("Missing required components to initialize orbit.");
        return;
    }

    auto& satellitePos = *ECS::Get().GetComponent<Position>(satelliteID);
    auto& attractorPos = *ECS::Get().GetComponent<Position>(attractorID);

    auto& satelliteRig = *ECS::Get().GetComponent<Rigidbody>(satelliteID);
    auto& attractorRig = *ECS::Get().GetComponent<Rigidbody>(attractorID);

    glm::vec3 direction = glm::normalize(attractorPos.GetWorld() - satellitePos.GetWorld());
    float distanceKm = glm::length(attractorPos.GetWorld() - satellitePos.GetWorld());

    double orbitalSpeed = CalculateOrbitalVelocity(attractorRig.mass, distanceKm * 2);

    // Compute tangential direction
    glm::vec3 up = glm::vec3(0, 1, 0);

    // If direction is nearly parallel with up, pick alternate
    if (std::abs(glm::dot(direction, up)) > 0.99f)
    {
        up = glm::vec3(1, 0, 0);
    }

    glm::vec3 tangential = glm::normalize(glm::cross(direction, up));
    glm::vec3 satelliteVel = tangential * static_cast<float>(orbitalSpeed);

    // Apply to satellite
    if (ECS::Get().HasComponent<Velocity>(satelliteID))
    {
        Velocity& velocity = *ECS::Get().GetComponent<Velocity>(satelliteID);

        velocity.SetWorld(velocity.GetWorld() + satelliteVel);
    } 
    else 
    {
        ECS::Get().AddComponent(satelliteID, Velocity{ satelliteVel });
    }

    // Conservation of momentum: Apply opposite to attractor
    glm::vec3 momentum = satelliteVel * static_cast<float>(satelliteRig.mass);
    glm::vec3 attractorDeltaVel = -momentum / static_cast<float>(attractorRig.mass);

    if (ECS::Get().HasComponent<Velocity>(attractorID)) 
    {
        Velocity& velocity = *ECS::Get().GetComponent<Velocity>(attractorID);

        velocity.SetWorld(velocity.GetWorld() + attractorDeltaVel);
    } 
    else
    {
        ECS::Get().AddComponent(attractorID, Velocity{ attractorDeltaVel });
    }

    spdlog::info("Initialized orbit:");
    spdlog::info(" - Satellite vel = ({:.2f}, {:.2f}, {:.2f})", satelliteVel.x, satelliteVel.y, satelliteVel.z);
    spdlog::info(" - Attractor vel = ({:.6f}, {:.6f}, {:.6f})", attractorDeltaVel.x, attractorDeltaVel.y, attractorDeltaVel.z);
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