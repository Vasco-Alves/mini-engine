#pragma once

#include <mini-engine/core/application.hpp>
#include <mini-engine/scene/scene.hpp>

#include <memory>

namespace sandbox {

	class SandboxGame : public me::Application {
	public:
		void on_start(int width, int height) override;
		void on_resize(int width, int height) override;
		void on_update(float dt) override;
		void on_render() override;
		void on_shutdown() override;

	public:
		std::shared_ptr<me::Scene> active_scene;
	};

} // namespace sandbox
