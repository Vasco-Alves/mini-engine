#include <mini-engine/core/engine.hpp>
#include <mini-engine/core/application.hpp>

#include "sandbox/core/Game.hpp"

int main() {
	me::AppConfig config;
	config.title = "My Game";
	config.width = 1920;
	config.height = 1080;
	config.vsync = false;

	sandbox::SandboxGame game;

	me::run(game, config);

	return 0;
}