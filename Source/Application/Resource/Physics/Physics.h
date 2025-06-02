#pragma once
#include <iostream>

#include <Application/Constants/Constants.h>
#include <Application/Resource/Components/Components.h>
#include <Application/Resource/EntityManager/EntityManager.h>

namespace Physics
{
	void Update(float deltaTime)
	{
        const auto& spheres = ECS::Get().GetAllComponents<Sphere>();
        const auto& sphereIDs = ECS::Get().GetAllComponentIDs<Sphere>();

        for (size_t i = 0; i < spheres.size(); ++i)
        {
            const EntityID& id = sphereIDs[i];

            if (!ECS::Get().HasComponent<Position>(id) || !ECS::Get().HasComponent<Velocity>(id))
                continue;

            auto& pos = *ECS::Get().GetComponent<Position>(id);
            const auto& vel = *ECS::Get().GetComponent<Velocity>(id);

            glm::vec3 next = pos.GetWorld() + vel.GetWorld() * deltaTime * TIME_SCALE;
            pos.SetWorld(next);
        }
	}
}