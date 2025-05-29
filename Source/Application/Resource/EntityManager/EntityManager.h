#pragma once
#include <Application/Core/Core.h>
#include <Application/Resource/Transform/Position.h>

namespace SpaceSim {
	enum class EntityType {
		NONE = 0,
		SPHERE = 1 << 0,
		CAMERA = 1 << 1,
		ALL = SPHERE | CAMERA
	};

	class Entity {
	public:
		Entity() = default;
		virtual ~Entity() = default;

		void SetName(const String& name) { m_name = name; }
		const String& GetName() const { return m_name; }

		void SetPosition(const Position& position) { m_position = position; }
		const Position& GetPosition() const { return m_position; }

	private:
		EntityID id;

		String m_name;
		Position m_position;
	};

	class EntityManager {
	public:
		EntityID CreateEntity() 
		{
			EntityID id;
			if (!m_freeList.empty())
			{
				id = m_freeList.back();
				m_freeList.pop_back();
			}
			else
			{
				id = m_nextID++;
			}

			m_alive[id] = true;
			return id;
		}

		void DestroyEntity(EntityID id)
		{
			m_alive[id] = false;
			m_freeList.push_back(id);
		}

		bool IsAlive(EntityID id) const
		{
			auto it = m_alive.find(id);
			return it != m_alive.end() && it->second;
		}

	private:
		EntityID m_nextID = 0;
		Vector<EntityID> m_freeList;
		HashMap<EntityID, bool> m_alive;
	};

	struct IComponentPool
	{
		virtual void Remove(EntityID id) = 0;
		virtual ~IComponentPool() = default;
	};

	template<typename T>
	class ComponentPool : public IComponentPool
	{
	public:
		void Add(EntityID id, const T& component)
		{
			assert(!Has(id));
			size_t index = component.size();
			entityToIndex[id] = index;
			indexToEntity.push_back(id);
		}

		void Remove(EntityID id) override
		{
			assert(Has(id));
			size_t index = entityToIndex[id];
			size_t last = components.size() - 1;

			std::swap(components[index], components[last]);
			std::swap(indexToEntity[index], indexToEntity[last]);
			entityToIndex[indexToEntity[index]] = index;

			components.pop_back();
			indexToEntity.pop_back();
			entityToIndex.erase(id);
		}

		bool Has(EntityID id) const
		{
			return entityToIndex.find(id) != entityToIndex.end();
		}

		T* Get(EntityID id)
		{
			auto it = entityToIndex.find(id);
			if (it != entityToIndex.end())
				return &components[it->second];

			return nullptr;
		}

		const Vector<T>& GetAll() const { return components; }

	private:
		Vector<T> components;
		Vector<EntityID> indexToEntity;
		HashMap<EntityID, size_t> entityToIndex;
	};

	class ECS
	{
	public:
		EntityID CreateEntity()
		{
			return m_entityManager.CreateEntity();
		}

		void DestroyEntity(EntityID id)
		{
			m_entityManager.DestroyEntity(id);
			for (auto& [_, pool] : m_componentPools)
			{
				pool->Remove(id);
			}
		}

		template<typename T>
		void AddComponent(EntityID id, const T& component)
		{
			GetOrCreatePool<T>().Add(id, component);
		}

		template<typename T>
		void RemoveComponent(EntityID id)
		{
			GetPool<T>().Remove(id);
		}

		template<typename T>
		bool HasComponent(EntityID id) {
			return GetPool<T>().Has(id);
		}

		template<typename T>
		T* GetComponent(EntityID id) {
			return GetPool<T>().Get(id);
		}

		template<typename T>
		const Vector<T>& GetAllComponents() {
			return GetPool<T>().GetAll();
		}

	private:
		template<typename T>
		ComponentPool<T>& GetPool()
		{
			auto it = m_componentPools.find(typeid(T));
			assert(it != m_componentPools.end());
			return *static_cast<ComponentPool<T>*>(it->second.get());
		}

		template<typename T>
		ComponentPool<T>& GetOrCreatePool()
		{
			auto it = m_componentPools.find(typeid(T));
			if (it == m_componentPools.end())
			{
				auto pool = MakeUnique<ComponentPool<T>>;
				m_componentPools[typeid(T)] = std::move(pool);
			}
			
			return *static_cast<ComponentPool<T>*>(m_componentPools[typeid(T)].get());
		}

		EntityManager m_entityManager;
		HashMap<TypeIndex, UniquePtr<IComponentPool>> m_componentPools;

		template<typename T>
		static void DeletePool(void* ptr)
		{
			delete static_cast<ComponentPool<T>*>(ptr);
		}
	};
}