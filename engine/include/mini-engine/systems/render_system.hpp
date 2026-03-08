#pragma once

#include <mini-engine/ecs/system.hpp>
#include <mini-engine/ecs/components.hpp>
#include <mini-engine/render/renderer.hpp>

namespace me {

	class MeshRenderSystem : public System {
	public:
		MeshRenderSystem(Registry& registry, entity::entity_id active_camera) : System(registry), m_active_camera(active_camera) {}

		void on_render() override;

	private:
		entity::entity_id m_active_camera;
	};

} // namespace me