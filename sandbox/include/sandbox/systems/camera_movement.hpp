#pragma once

#include <mini-engine/ecs/system.hpp>

#include <mini-ecs/registry.hpp>

namespace sandbox::systems {

	class CameraMovementSystem : public me::System {
	public:
		CameraMovementSystem(me::Registry& registry, me::entity::entity_id camera);

		void on_update(float dt) override;

	private:
		me::entity::entity_id m_camera;
	};

}
