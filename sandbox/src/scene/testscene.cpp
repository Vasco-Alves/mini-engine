#include "sandbox/scene/testscene.hpp"

#include <mini-engine/ecs/components.hpp>
#include <mini-engine/render/renderer.hpp>
#include <mini-engine/input/input.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <print>
#include <string>

namespace sandbox {

	void TestScene::on_start(int width, int height) {
		std::println("Game Started!");

		// --- Input Binding ---
		me::input::bind_action("Quit", me::input::Key::Escape);

		// Movement
		me::input::bind_action("Left", me::input::Key::A);
		me::input::bind_action("Right", me::input::Key::D);
		me::input::bind_action("Forward", me::input::Key::W);
		me::input::bind_action("Backward", me::input::Key::S);
		me::input::bind_action("Up", me::input::Key::Q);
		me::input::bind_action("Down", me::input::Key::E);

		// -- Camera Initialization --
		float aspectRatio = (float)width / (float)height;
		camera = std::make_unique<me::camera::PerspectiveCamera>(45.0f, aspectRatio, 0.1f, 100.0f);
		cameraPos = { 0.0f, 0.0f, 20.0f };
		camera->set_position(cameraPos);

		// -- Entity Creation --
		auto cube_mesh = me::Mesh::create_cube();

		int index = 0;
		for (int x = -2; x <= 2; x++) {
			for (int y = -2; y <= 2; y++) {
				auto entity = registry.create_entity("Cube_" + std::to_string(index++));

				// TransformComponent
				me::components::TransformComponent t{};
				t.position = { x * 1.5f, y * 1.5f, 0.0f };
				registry.add_component(entity, t);

				// MeshComponent
				glm::vec4 color = { (x + 3) / 5.0f, 0.2f, (y + 3) / 5.0f, 1.0f };
				me::components::MeshComponent m(cube_mesh, color);
				registry.add_component(entity, m);
			}
		}
	}

	void TestScene::on_resize(int width, int height) {
		if (height == 0)
			return;

		if (camera) {
			float aspectRatio = (float)width / (float)height;
			camera->set_projection(45.0f, aspectRatio, 0.1f, 100.0f);
		}
	}

	void TestScene::on_update(float dt) {
		// Move Camera
		if (me::input::action_down("Left")) cameraPos.x -= cameraSpeed * dt;
		if (me::input::action_down("Right")) cameraPos.x += cameraSpeed * dt;
		if (me::input::action_down("Forward")) cameraPos.z -= cameraSpeed * dt;
		if (me::input::action_down("Backward")) cameraPos.z += cameraSpeed * dt;
		if (me::input::action_down("Up")) cameraPos.y += cameraSpeed * dt;
		if (me::input::action_down("Down")) cameraPos.y -= cameraSpeed * dt;

		camera->set_position(cameraPos);

		// --- Update transform system ---
		auto& transform_pool = registry.view<me::components::TransformComponent>();

		for (size_t i = 0; i < transform_pool.size(); i++) {
			auto& transform = transform_pool.components[i];

			transform.rotation.x += 45.0f * dt;
			transform.rotation.y += 45.0f * dt;

			if (transform.rotation.x >= 360.0f)
				transform.rotation.x -= 360.0f;

			if (transform.rotation.y >= 360.0f)
				transform.rotation.y -= 360.0f;
		}
	}

	void TestScene::on_render() {
		me::Renderer::begin_scene(*camera);

		// -- Render system --
		auto& mesh_pool = registry.view<me::components::MeshComponent>(); // TODO: implement view<A,B,...>() in ECS

		for (size_t i = 0; i < mesh_pool.size(); i++) {
			auto& mesh_comp = mesh_pool.components[i];
			me::entity::entity_id e = mesh_pool.entity_map[i];

			auto* transform = registry.try_get_component<me::components::TransformComponent>(e);

			if (transform)
				me::Renderer::draw_mesh(mesh_comp.mesh, transform->get_transform(), mesh_comp.color);
		}

		me::Renderer::end_scene();
	}

	void TestScene::on_close() {
		std::println("Game Over!");
	}

} // namespace sandbox
