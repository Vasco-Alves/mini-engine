#include <mini-engine/engine.hpp>
#include <mini-engine/registry.hpp>
#include <mini-engine/components.hpp>
#include <mini-engine/input.hpp>

#include <iostream>

class SandboxGame : public me::Application {
public:
	me::Entity player;
	me::Entity player2;

	void on_start() override {
		std::cout << "Game Started!" << std::endl;

		// --- Input Binding ---
		me::input::bind_action("Quit", me::input::Key::Escape);

		// --- Entity Creation ---
		me::Registry& reg = me::get_registry();

		player = reg.create_entity("Player");
		player.add_component(me::components::Transform{ 0, 0, 0 });
		std::cout << "Created Entity ID: " << player.id() << std::endl;

		player2 = reg.create_entity("Player2");
		player2.add_component(me::components::Transform{ 0, 0, 0 });
		std::cout << "Created Entity ID: " << player2.id() << std::endl;
	}

	void on_update(float dt) override {
		if (me::input::action_pressed("Quit"))
			me::close_application();
	}

	void on_render() override {
	}

	void on_shutdown() override {
		std::cout << "Game Over!" << std::endl;
	}
};

int main() {
	SandboxGame game;

	me::AppConfig config;
	config.title = "My Game";
	config.width = 1920;
	config.height = 1080;
	config.vsync = false;

	me::run(game, config);

	return 0;
}