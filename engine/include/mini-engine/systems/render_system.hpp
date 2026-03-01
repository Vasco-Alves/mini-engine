#pragma once

#include <mini-engine/ecs/system.hpp>
#include <mini-engine/ecs/components.hpp>
#include <mini-engine/render/renderer.hpp>

namespace me {

	class MeshRenderSystem : public System {
	public:
		MeshRenderSystem(Registry& registry, entity::entity_id active_camera) : System(registry), m_active_camera(active_camera) {}

		void on_render() override {
			// --- 1. Setup Camera ---
			auto* cam_transform = m_registry.try_get_component<components::TransformComponent>(m_active_camera);
			auto* cam_comp = m_registry.try_get_component<components::CameraComponent>(m_active_camera);

			if (cam_transform && cam_comp) {
				glm::mat4 view = glm::inverse(cam_transform->get_transform());
				glm::mat4 projection;

				if (cam_comp->type == components::CameraComponent::ProjectionType::Perspective) {
					projection = glm::perspective(glm::radians(cam_comp->fov), cam_comp->aspect_ratio, cam_comp->near_clip, cam_comp->far_clip);
				} else {
					float ortho = cam_comp->ortho_size;
					float aspect = cam_comp->aspect_ratio;
					projection = glm::ortho(-ortho * aspect, ortho * aspect, -ortho, ortho, cam_comp->near_clip, cam_comp->far_clip);
				}

				Renderer::begin_scene(projection * view);
			} else {
				Renderer::begin_scene(glm::mat4(1.0f));
			}

			// --- 2. Draw Meshes ---
			auto& mesh_pool = m_registry.view<components::MeshComponent>();

			for (size_t i = 0; i < mesh_pool.size(); i++) {
				auto& mesh_comp = mesh_pool.components[i];
				entity::entity_id e = mesh_pool.entity_map[i];

				auto* transform = m_registry.try_get_component<components::TransformComponent>(e);

				if (transform) {
					Renderer::draw_mesh(mesh_comp.mesh, transform->get_transform(), mesh_comp.color);
				}
			}

			Renderer::end_scene();
		}

	private:
		entity::entity_id m_active_camera;
	};

} // namespace me