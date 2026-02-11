#include <mini-engine/engine.hpp>
#include <mini-engine/registry.hpp>
#include <mini-engine/components.hpp>
#include <iostream>

class SandboxGame : public me::Application {
public:
	me::Entity player;
	float moveSpeed = 100.0f;

	void on_start() override {
		std::cout << "Game Started!" << std::endl;

		me::Registry& reg = me::get_registry();

		// Create Player
		player = reg.create_entity("Player");
		player.add_component(me::components::Transform{ 0, 0, 0 });

		std::cout << "Created Entity ID: " << player.id() << std::endl;
	}

	void on_update(float dt) override {
	}

	void on_render() override {
	}

	void on_shutdown() override {
		std::cout << "Game Over!" << std::endl;
	}
};

int main() {
	SandboxGame game;

	// Option A: Use defaults
	// me::run(game);

	// Option B: Custom Settings
	me::AppConfig config;
	config.title = "My Game";
	config.width = 1920;
	config.height = 1080;
	config.vsync = true;

	me::run(game);

	return 0;
}