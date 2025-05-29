#pragma once

#include <Application/Core/Core.h>
#include <Application/Resource/EntityManager/EntityManager.h>
#include <Application/Resource/Sphere/Sphere.h>

namespace SpaceSim {
	class Scene {
	public:
		Scene();
		Scene(const HashMap<EntityType, Entity>& entities);
		~Scene();

		void AddPlanet(SphereDesc& sphereDesc);
		void AddCamera(CameraDesc& cameraDesc);

		SharedPtr<Sphere> GetPlanet();
		SharedPtr<Camera> GetCamera();

	private:
		HashMap<EntityType, Entity> m_entities;
	};
}