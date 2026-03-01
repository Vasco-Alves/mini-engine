#include "sandbox/scene/testscene.hpp"
#include "sandbox/systems/camera_movement.hpp"
#include "sandbox/systems/cube_rotation.hpp"

#include <mini-engine/ecs/components.hpp>
#include <mini-engine/render/renderer.hpp>
#include <mini-engine/input/input.hpp>
#include <mini-engine/systems/render_system.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <print>
#include <string>

namespace sandbox {

	void TestScene::on_start(int width, int height) {
		std::println("Game Started!");

		// --- Input Binding ---
		me::input::bind_action("Quit", me::input::Key::Escape);
		me::input::bind_action("Forward", me::input::Key::W);
		me::input::bind_action("Backward", me::input::Key::S);
		me::input::bind_action("Left", me::input::Key::A);
		me::input::bind_action("Right", me::input::Key::D);
		me::input::bind_action("Up", me::input::Key::Q);
		me::input::bind_action("Down", me::input::Key::E);

		// -- Camera Initialization --
		main_camera = m_registry.create_entity("MainCamera");

		me::components::TransformComponent cam_transform;
		cam_transform.position = { 0.0f, 0.0f, 20.0f };
		m_registry.add_component(main_camera, cam_transform);

		me::components::CameraComponent cam_comp;
		cam_comp.fov = 45.0f;
		if (height > 0) cam_comp.aspect_ratio = (float)width / (float)height;
		m_registry.add_component(main_camera, cam_comp);

		// -- Entity Creation --
		auto cube_mesh = me::Mesh::create_cube();

		int index = 0;
		for (int x = -2; x <= 2; x++) {
			for (int y = -2; y <= 2; y++) {
				auto entity = m_registry.create_entity("Cube_" + std::to_string(index++));

				me::components::TransformComponent t{};
				t.position = { x * 1.5f, y * 1.5f, 0.0f };
				m_registry.add_component(entity, t);

				glm::vec4 color = { (x + 3) / 5.0f, 0.2f, (y + 3) / 5.0f, 1.0f };
				me::components::MeshComponent m(cube_mesh, color);
				m_registry.add_component(entity, m);
			}
		}

		// --- Register systems ---
		// Logic Systems (Sandbox)
		add_system<CameraMovementSystem>(main_camera);
		add_system<CubeRotationSystem>(main_camera);

		// Render Systems (Engine)
		add_system<me::MeshRenderSystem>(main_camera);
	}

	void TestScene::on_resize(int width, int height) {
		if (height == 0) return;

		// Update the camera's aspect ratio
		auto* cam_comp = m_registry.try_get_component<me::components::CameraComponent>(main_camera);
		if (cam_comp) cam_comp->aspect_ratio = (float)width / (float)height;
	}

	void TestScene::on_update(float dt) {
		me::Scene::on_update(dt);
	}

	void TestScene::on_render() {
		me::Scene::on_render();
	}

	void TestScene::on_close() {
		std::println("Game Over!");
	}

} // namespace sandbox