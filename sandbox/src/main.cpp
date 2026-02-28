#include <mini-engine/core/engine.hpp>
#include <mini-engine/input/input.hpp>
#include <mini-engine/scene/scene.hpp>

#include "sandbox/scene/testscene.hpp"

class SandboxGame : public me::Application {
public:
	void on_start(int width, int height) override {
		active_scene = std::make_shared<sandbox::TestScene>();
		active_scene->on_start(width, height);
	}

	void on_resize(int width, int height) override {
		active_scene->on_resize(width, height);
	}

	void on_update(float dt) override {
		if (me::input::action_pressed("Quit")) {
			active_scene->on_close();
			me::close_application();
		}

		active_scene->on_update(dt);
	}

	void on_render() override {
		active_scene->on_render();
	}

	void on_shutdown() override {
		active_scene->on_close();
	}

public:
	std::shared_ptr<me::Scene> active_scene;
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