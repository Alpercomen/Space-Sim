#pragma once

/*
* BASE CLASS
*/

#include "Entity.h"

#include <Application/Core/Core.h>
#include <Application/Resource/Components/Transform/Position/Position.h>

namespace SpaceSim {
	class Entity {
	public:
		Entity() = default;
		virtual ~Entity() = default;

		virtual void Update(float deltaTime) = 0;
		virtual void Draw() = 0;

		void SetPosition(const Position& pos) { m_pos = pos; }
		Position GetPosition() const { return m_pos; }

		void SetName(const String& name) { m_name = name; }
		const String& GetName() const { return m_name; }
		
	private:
		String m_name = "NO_NAME";
		Position m_pos = glm::vec3(0.0);
	};
}