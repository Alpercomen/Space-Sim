#pragma once
#include <Application/Core/Core.h>
#include <Application/Resource/Components/Transform/Position/Position.h>

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
		String m_name;
		Position m_position;
	};
}