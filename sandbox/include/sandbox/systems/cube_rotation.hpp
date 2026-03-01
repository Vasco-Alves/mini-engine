#pragma once

#include <mini-engine/ecs/system.hpp>
#include <mini-engine/ecs/components.hpp>

#include <mini-ecs/registry.hpp>

namespace sandbox {

	class CubeRotationSystem : public me::System {
	public:
		CubeRotationSystem(me::Registry& registry, me::entity::entity_id camera) : me::System(registry), m_camera(camera) {}

		void on_update(float dt) override {
			auto& transform_pool = m_registry.view<me::components::TransformComponent>();

			for (size_t i = 0; i < transform_pool.size(); i++) {
				me::entity::entity_id e = transform_pool.entity_map[i];

				if (e == m_camera) continue;

				auto& transform = transform_pool.components[i];

				transform.rotation.x += 45.0f * dt;
				transform.rotation.y += 45.0f * dt;

				if (transform.rotation.x >= 360.0f) transform.rotation.x -= 360.0f;
				if (transform.rotation.y >= 360.0f) transform.rotation.y -= 360.0f;
			}
		}

	private:
		me::entity::entity_id m_camera;
	};

}
