#pragma once

#include <Application/Core/Core.h>
#include <Application/Resource/EntityManager/EntityManager.h>

namespace SpaceSim {
	class Scene {
	public:
		Scene();
		Scene(const HashMap<EntityType, Entity>& entities);
		~Scene();

	private:
		HashMap<EntityType, Entity> m_entities;
	};

	class SceneManager {
	public:

	private:
		
	};
}