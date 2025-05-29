#pragma once

#include "Scene.h"

namespace SpaceSim {
	Scene::Scene() : Scene(HashMap<EntityType, Entity>()) {}

	Scene::Scene(const HashMap<EntityType, Entity>& entities)
	{
		m_entities = entities;
	}

	Scene::~Scene() = default;

	void Scene::AddPlanet(SphereDesc& sphereDesc)
	{
	}

	void Scene::AddCamera(CameraDesc& cameraDesc)
	{
	}


}