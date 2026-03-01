#pragma once

#include <mini-engine/scene/scene.hpp>
#include <mini-engine/render/perspective_camera.hpp>

namespace sandbox {

	class TestScene : public me::Scene {
	public:
		void on_start(int width, int height) override;
		void on_resize(int width, int height) override;
		void on_update(float dt) override;
		void on_render() override;
		void on_close() override;

	private:
		std::unique_ptr<me::camera::PerspectiveCamera> camera;
		glm::vec3 cameraPos = { 0.0f, 0.0f, 3.0f };
		float cameraSpeed = 1.0f;

		float cubeRotation = 0.0f;
	};

} // namespace sandbox
