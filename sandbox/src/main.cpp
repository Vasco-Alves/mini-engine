#include <mini-engine/core/engine.hpp>
//#include <mini-engine/components.hpp>
#include <mini-engine/input/input.hpp>
#include <mini-engine/render/renderer.hpp>
#include <mini-engine/render/perspective_camera.hpp>

//#include <mini-ecs/registry.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <print>

class SandboxGame : public me::Application {
public:
	void on_start(int width, int height) override {
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
		camera->set_position(cameraPos);
	}

	void on_resize(int width, int height) override {

		this->width = width;
		this->height = height;

		if (height == 0)
			return;

		if (camera) {
			float aspectRatio = (float)width / (float)height;
			camera->set_projection(45.0f, aspectRatio, 0.1f, 100.0f);
		}
	}

	void on_update(float dt) override {
		if (me::input::action_pressed("Quit"))
			me::close_application();

		// Move Camera
		if (me::input::action_down("Left")) cameraPos.x -= cameraSpeed * dt;
		if (me::input::action_down("Right")) cameraPos.x += cameraSpeed * dt;
		if (me::input::action_down("Forward")) cameraPos.z -= cameraSpeed * dt;
		if (me::input::action_down("Backward")) cameraPos.z += cameraSpeed * dt;
		if (me::input::action_down("Up")) cameraPos.y += cameraSpeed * dt;
		if (me::input::action_down("Down")) cameraPos.y -= cameraSpeed * dt;

		camera->set_position(cameraPos);

		cubeRotation += 45.0f * dt;
		if (cubeRotation >= 360.0f)
			cubeRotation = 0.0f;
	}

	void on_render() override {
		me::Renderer::begin_scene(*camera);

		// Create a transform for the cube: placed at center, rotated on X and Y axes
		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(cubeRotation), glm::vec3(1.0f, 1.0f, 0.0f)) *
			glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));

		// Draw a green cube!
		me::Renderer::draw_cube(transform, { 0.2f, 0.8f, 0.3f, 1.0f });

		me::Renderer::end_scene();
	}


	void on_shutdown() override {
		std::println("Game Over!");
	}

public:
	std::unique_ptr<me::camera::PerspectiveCamera> camera;
	glm::vec3 cameraPos = { 0.0f, 0.0f, 3.0f };
	float cameraSpeed = 1.0f;

	float cubeRotation = 0.0f;
};

int main() {
	me::AppConfig config;
	config.title = "My Game";
	config.width = 1920;
	config.height = 1080;
	config.vsync = false;

	SandboxGame game;

	me::run(game, config);

	return 0;
}