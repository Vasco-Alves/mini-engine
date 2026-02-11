#include "mini-engine/engine.hpp"
#include "mini-engine/registry.hpp"
#include "mini-engine/input.hpp"

#include <modulus/core/context.hpp>
#include <modulus/platform/platform.hpp>
#include <modulus/gfx/graphics.hpp>
#include <modulus/core/log.hpp>

#include <memory>
#include <chrono>

namespace me {

	struct EngineState {
		std::unique_ptr<modulus::Context> context;
		std::unique_ptr<modulus::platform::IWindow> window;
		std::unique_ptr<Registry> registry;
		AppConfig config;
		bool running = false;
	};

	static EngineState s_State;

	// Internal initialization function
	bool internal_init(const AppConfig& config) {
		s_State.config = config;

		// 1. Modulus Init
		s_State.context = std::make_unique<modulus::Context>();
		if (!s_State.context->is_valid()) return false;

		modulus::platform::WindowConfig winConfig;
		winConfig.title = config.title;
		winConfig.width = config.width;
		winConfig.height = config.height;
		winConfig.vsync = config.vsync;

		s_State.window = modulus::platform::create_window(winConfig);
		if (!s_State.window) return false;

		if (!modulus::gfx::init()) return false;

		// 2. ECS Init
		s_State.registry = std::make_unique<Registry>();

		MOD_INFO("Mini Engine Initialized.");
		s_State.running = true;
		return true;
	}

	void run(Application& app, const AppConfig& config) {
		// 1. Initialize System
		if (!internal_init(config)) {
			MOD_FATAL("Engine failed to initialize!");
			return;
		}

		// 2. User Start
		app.on_start();

		// 3. Main Loop
		using Clock = std::chrono::high_resolution_clock;
		auto last_time = Clock::now();

		double accumulator = 0.0;
		int frames = 0;

		while (s_State.running && s_State.window->update()) {
			auto current_time = Clock::now();
			std::chrono::duration<double> diff = current_time - last_time;
			last_time = current_time;
			float dt = static_cast<float>(diff.count());

			// --- FPS Counter Logic ---
			accumulator += dt;
			frames++;
			if (accumulator >= 1.0) {
				// We use the original title from config and append FPS
				std::string title = s_State.config.title + " | FPS: " + std::to_string(frames);
				s_State.window->set_title(title);
				frames = 0;
				accumulator = 0.0;
			}

			// User Update
			app.on_update(dt);

			// Render Prep
			modulus::gfx::clear({ 0.1f, 0.1f, 0.12f, 1.0f });

			// User Render
			app.on_render();

			// Render Present
			modulus::gfx::present(*s_State.window);

			me::input::poll();
		}

		// 4. User Shutdown
		app.on_shutdown();

		// 5. Engine Cleanup
		s_State.registry.reset();
		s_State.window.reset();
		s_State.context.reset();
		MOD_INFO("Mini Engine Shutdown.");
	}

	Registry& get_registry() {
		return *s_State.registry;
	}

	void close_application() {
		s_State.running = false;
	}

} // namespace me