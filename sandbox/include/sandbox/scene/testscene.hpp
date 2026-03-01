#pragma once

#include <mini-engine/scene/scene.hpp>
#include <mini-ecs/entity.hpp> 

namespace sandbox {

	class TestScene : public me::Scene {
	public:
		void on_start(int width, int height) override;
		void on_resize(int width, int height) override;
		void on_update(float dt) override;
		void on_render() override;
		void on_close() override;

	private:
		me::entity::entity_id main_camera;

		float cameraSpeed = 5.0f;
	};

} // namespace sandbox