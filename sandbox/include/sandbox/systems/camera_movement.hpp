#pragma once

#include <mini-engine/ecs/system.hpp>
#include <mini-engine/ecs/components.hpp>
#include <mini-engine/input/input.hpp>

#include <mini-ecs/registry.hpp>

namespace sandbox {

	class CameraMovementSystem : public me::System {
	public:
		// We pass the camera entity ID so the system knows what to move
		CameraMovementSystem(me::Registry& registry, me::entity::entity_id camera)
			: me::System(registry), m_camera(camera) {}

		void on_update(float dt) override {
			auto* transform = m_registry.try_get_component<me::components::TransformComponent>(m_camera);
			if (!transform) return;

			float speed = 5.0f;
			if (me::input::action_down("Left")) transform->position.x -= speed * dt;
			if (me::input::action_down("Right")) transform->position.x += speed * dt;
			if (me::input::action_down("Forward")) transform->position.z -= speed * dt;
			if (me::input::action_down("Backward")) transform->position.z += speed * dt;
			if (me::input::action_down("Up")) transform->position.y += speed * dt;
			if (me::input::action_down("Down")) transform->position.y -= speed * dt;
		}

	private:
		me::entity::entity_id m_camera;
	};

}
