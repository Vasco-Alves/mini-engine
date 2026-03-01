#include "sandbox/core/game.hpp"
#include "sandbox/scene/testscene.hpp"

#include <mini-engine/input/input.hpp>
#include <mini-engine/core/engine.hpp>

namespace sandbox {

	void SandboxGame::on_start(int width, int height) {
		active_scene = std::make_shared<sandbox::TestScene>();
		active_scene->on_start(width, height);
	}

	void SandboxGame::on_resize(int width, int height) {
		active_scene->on_resize(width, height);
	}

	void SandboxGame::on_update(float dt) {
		if (me::input::action_pressed("Quit")) {
			active_scene->on_close();
			me::close_application();
		}

		active_scene->on_update(dt);
	}

	void SandboxGame::on_render() {
		active_scene->on_render();
	}

	void SandboxGame::on_shutdown() {
		active_scene->on_close();
	}

}
