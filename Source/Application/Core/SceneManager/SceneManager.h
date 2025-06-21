#pragma once

#include <Application/Core/Core.h>
#include <Application/Resource/EntityManager/EntityManager.h>
#include <Application/Resource/Components/Components.h>
#include <Application/Resource/Utils/SpaceUtils/SpaceUtils.h>

namespace Nyx {
	using SceneID = uint32;
	using CameraID = uint32;

	class SceneObject
	{
	public:
		SceneObject(String name)
		{
			m_entityID = ECS::Get().CreateEntity();
			ECS::Get().AddComponent(m_entityID, Name{ name });
		}

		~SceneObject()
		{
			ECS::Get().DestroyEntity(m_entityID);
		}

		EntityID GetEntityID()
		{
			return m_entityID;
		}

		void Draw(const Camera& camera)
		{
			const auto& transform = ECS::Get().GetComponent<Transform>(m_entityID);
			if (!transform)
				return;

			const auto& pos = transform->position;
			const auto& rot = transform->rotation;
			const auto& sca = transform->scale;

			glm::mat4 model = glm::translate(Math::Mat4f(1.0f), pos.GetWorld()) * rot.toMatrix() * sca.toMatrix();
			glm::mat4 view = camera.GetViewMatrix();
			glm::mat4 projection = camera.GetProjectionMatrix();

			glm::mat4 mvp = projection * view * model;

			if (ECS::Get().HasComponent<Sphere>(m_entityID))
			{
				const auto& sphere = ECS::Get().GetComponent<Sphere>(m_entityID);
				sphere->DrawSphere(mvp);
			}
		}

	private:
		EntityID m_entityID;
	};

	class Scene 
	{
	public:
		Scene() = default;
		~Scene() = default;

		CameraID GetActiveCameraID() const
		{
			if (m_activeCameraID != NO_ID && ECS::Get().HasComponent<Camera>(m_activeCameraID))
				return m_activeCameraID;

			return NO_ID;
		}

		EntityID CreateEmptyEntity(String name)
		{
			SharedPtr<SceneObject> obj = MakeShared<SceneObject>(name);

			m_sceneObjectPtrs[obj->GetEntityID()] = obj;
			return obj->GetEntityID();
		}

		EntityID CreatePlanet(String name, const Transform& transform, const Rigidbody& rigidbody, const SphereDesc& sphereDesc)
		{
			SharedPtr<SceneObject> obj = MakeShared<SceneObject>(name);

			ECS::Get().AddComponent(obj->GetEntityID(), Sphere{sphereDesc});
			ECS::Get().AddComponent(obj->GetEntityID(), transform);
			ECS::Get().AddComponent(obj->GetEntityID(), rigidbody);

			m_sceneObjectPtrs[obj->GetEntityID()] = obj;
			return obj->GetEntityID();
		}

		EntityID CreateCamera(String name, const Transform& transform)
		{
			SharedPtr<SceneObject> obj = MakeShared<SceneObject>(name);
			ECS::Get().AddComponent(obj->GetEntityID(), Camera{});
			ECS::Get().AddComponent(obj->GetEntityID(), transform);

			// Only set if valid
			if (ECS::Get().HasComponent<Camera>(obj->GetEntityID()))
			{
				m_activeCameraID = obj->GetEntityID();
			}
			else 
			{
				m_activeCameraID = NO_ID;
			}

			m_sceneObjectPtrs[obj->GetEntityID()] = obj;
			return obj->GetEntityID();
		}

		SharedPtr<SceneObject> GetSceneObject(const EntityID& entityID)
		{
			if (m_sceneObjectPtrs.find(entityID) != m_sceneObjectPtrs.end())
				return m_sceneObjectPtrs[entityID];

			spdlog::critical("SceneObject with given ID does not exist!");
			return nullptr;
		}

		uint32 GetSceneObjectSize() { return m_sceneObjectPtrs.size(); }

	private:
		CameraID m_activeCameraID = NO_ID;
		HashMap<EntityID, SharedPtr<SceneObject>> m_sceneObjectPtrs;
	};

	class SceneManager 
	{
	public:
		SceneID CreateScene()
		{
			SceneID sceneID = 1;
			while (m_scenes.contains(sceneID)) 
				++sceneID;

			if (sceneID == NO_ID) 
			{
				spdlog::critical("SceneID overflow: exhausted all SceneIDs!");
				return NO_ID;
			}

			Scene newScene;
			m_scenes[sceneID] = newScene;
			m_activeSceneID = sceneID;

			return sceneID;
		}

		void DeleteScene(SceneID& id)
		{
			auto it = m_scenes.find(id);

			if (it == m_scenes.end()) 
			{
				spdlog::critical("Could not delete the scene with the given ID = {} ", id);
				return;
			}
			
			m_scenes.erase(it);
		}

		Scene* GetScene(SceneID& id)
		{
			auto it = m_scenes.find(id);
			if (it != m_scenes.end())
				return &m_scenes[id];

			spdlog::critical("Could not get the scene with the given ID = {} ", id);
			return nullptr;
		}

		void SetActiveScene(SceneID id) 
		{
			if (m_scenes.find(id) != m_scenes.end())
				m_activeSceneID = id;
			else
				spdlog::error("Scene ID {} does not exist!", id);
		}

		Scene* GetActiveScene() 
		{
			if (m_scenes.find(m_activeSceneID) != m_scenes.end())
				return &m_scenes[m_activeSceneID];
			return nullptr;
		}

		void GenerateEntities(SceneID& sceneID)
		{
			Scene* scenePtr = GetScene(sceneID);

			if (scenePtr == nullptr)
				return;

			SphereDesc earthDesc;
			earthDesc.res = 50;
			earthDesc.topColor = glm::vec3(0.28, 0.56, 0.93);
			earthDesc.botColor = glm::vec3(0.11, 0.23, 0.37);

			SphereDesc moonDesc;
			moonDesc.res = 50;
			moonDesc.topColor = glm::vec3(0.89, 0.96, 0.96);
			moonDesc.botColor = glm::vec3(0.30, 0.41, 0.41);

			EntityID earthID = scenePtr->CreatePlanet("Earth", Transform{ Position{}, Rotation{}, Scale{ 25.0 } }, Rigidbody{ 5.972e24 }, earthDesc);
			EntityID moonID = scenePtr->CreatePlanet("Moon", Transform{ glm::vec3(384.400, 0.0f, 0.0f), Rotation{}, Scale{ 6.0 } }, Rigidbody{ 7.342e22 }, moonDesc);
			EntityID cameraID = scenePtr->CreateCamera("Camera", Transform{ glm::vec3(0.0f, 0.0f, 100.0f) });

			InitializeCircularOrbit(moonID, earthID);
		}

	private:
		SceneID m_activeSceneID = NO_ID;
		HashMap<SceneID, Scene> m_scenes;
	};
}