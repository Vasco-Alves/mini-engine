#include "sandbox/core/game.hpp"
#include "sandbox/scene/testscene.hpp"

#include <mini-engine/input/input.hpp>
#include <mini-engine/core/engine.hpp>

namespace sandbox {

	void SandboxGame::on_start(int width, int height) {
		load_scene(std::make_shared<TestScene>(), width, height);
	}

	void SandboxGame::on_update(float dt) {
		if (me::input::action_pressed("Quit")) {
			me::close_application();
		}

		m_active_scene->on_update(dt);
	}

}
