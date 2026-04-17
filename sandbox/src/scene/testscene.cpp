#include "sandbox/scene/testscene.hpp"
#include "sandbox/systems/camera_movement.hpp"
#include "sandbox/systems/cube_rotation.hpp"

#include <mini-engine/ecs/components.hpp>
#include <mini-engine/render/renderer.hpp>
#include <mini-engine/input/input.hpp>
#include <mini-engine/systems/render_system.hpp>
#include <mini-engine/render/assets.hpp>

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

		me::input::bind_action("RotateU", me::input::Key::Up);
		me::input::bind_action("RotateD", me::input::Key::Down);
		me::input::bind_action("RotateL", me::input::Key::Left);
		me::input::bind_action("RotateR", me::input::Key::Right);

		// -- Camera Creation --
		main_camera = m_registry.create_entity("MainCamera");

		me::components::TransformComponent cam_transform;
		cam_transform.position = { 0.0f, 0.0f, 0.0f };
		m_registry.add_component(main_camera, cam_transform);

		me::components::CameraComponent cam_comp;
		cam_comp.fov = 45.0f;
		if (height > 0) cam_comp.aspect_ratio = (float)width / (float)height;
		m_registry.add_component(main_camera, cam_comp);

		// -- Cube Creation --
		// 1. Load the assets
		auto vert_src = me::File::read_text("assets/shaders/texture.vert");
		auto frag_src = me::File::read_text("assets/shaders/texture.frag");
		if (!vert_src || !frag_src) {
			std::println("ERROR: Could not find shader files!");
			return;
		}

		auto tex_shader = std::make_shared<me::Shader>(vert_src.value(), frag_src.value());
		auto crate_texture = std::make_shared<me::Texture>("assets/textures/crate.png");

		// 2. Create the Material
		auto crate_mat = std::make_shared<me::Material>(tex_shader);
		crate_mat->set_texture("u_Texture", crate_texture);
		crate_mat->set_color({ 1.0f, 1.0f, 1.0f, 1.0f }); // White tint (original colors)

		// 3. Add Components to the Cube

		// Cube 1
		auto textured_cube = m_registry.create_entity("TexturedCube");

		me::components::TransformComponent t{};
		t.position = { 0.0f, 0.0f, -5.0f };
		m_registry.add_component(textured_cube, t);

		me::components::MeshComponent m(me::Mesh::create_cube());
		m.material = crate_mat;
		m_registry.add_component(textured_cube, m);

		// Cube 2
		auto textured_cube2 = m_registry.create_entity("TexturedCube2");

		me::components::TransformComponent t2{};
		t2.position = { 0.0f, 0.0f, 5.0f };
		m_registry.add_component(textured_cube2, t2);

		me::components::MeshComponent m2(me::Mesh::create_cube());
		m2.material = crate_mat;
		m_registry.add_component(textured_cube2, m2);

		// --- Register systems ---
		// Logic Systems (Sandbox)
		add_system<systems::CameraMovementSystem>(main_camera);
		add_system<systems::CubeRotationSystem>(main_camera);

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