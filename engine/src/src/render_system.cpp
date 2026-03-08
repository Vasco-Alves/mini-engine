#include "mini-engine/systems/render_system.hpp"

#include <modulus/gfx/graphics.hpp>

namespace me {

	void MeshRenderSystem::on_render() {
		// --- 1. Setup Camera ---
		auto* cam_transform = m_registry.try_get_component<components::TransformComponent>(m_active_camera);
		auto* cam_comp = m_registry.try_get_component<components::CameraComponent>(m_active_camera);

		glm::mat4 view_proj = glm::mat4(1.0f);

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

			view_proj = projection * view;
			Renderer::begin_scene(view_proj);
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
				// CASE A: The entity has a Material
				if (mesh_comp.material) {
					mesh_comp.material->bind();

					// Pass the camera matrix to the material's shader!
					mesh_comp.material->get_shader()->set_mat4("u_ViewProjection", view_proj);

					// Pass the model transform
					mesh_comp.material->get_shader()->set_mat4("u_Transform", transform->get_transform());

					// Bind the Vertex Array and draw
					mesh_comp.mesh->get_vao()->bind();
					modulus::gfx::draw_indexed(mesh_comp.mesh->get_vao());
				}

				// CASE B: Fallback (No Material) uses the default renderer
				else {
					Renderer::draw_mesh(mesh_comp.mesh, transform->get_transform(), mesh_comp.color);
				}
			}
		}

		Renderer::end_scene();

	}

}
