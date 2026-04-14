#pragma once

#include <mini-engine/core/application.hpp>

#include <memory>

namespace sandbox {

	class SandboxGame : public me::Application {
	public:
		void on_start(int width, int height) override;
		void on_update(float dt) override;
	};

} // namespace sandbox
