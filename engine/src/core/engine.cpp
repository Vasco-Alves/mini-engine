#include "mini-engine/core/engine.hpp"
#include "mini-engine/input/input.hpp"
#include "mini-engine/render/renderer.hpp"

#include <modulus/core/context.hpp>
#include <modulus/core/log.hpp>
#include <modulus/core/timer.hpp>
#include <modulus/platform/platform.hpp>
#include <modulus/gfx/graphics.hpp>

#include <mini-ecs/registry.hpp>

#include <memory>

namespace me {

	struct EngineState {
		std::unique_ptr<modulus::Context> context;
		std::unique_ptr<modulus::platform::IWindow> window;
		std::unique_ptr<Registry> registry;
		AppConfig config;
		bool running = false;
	};

	static EngineState s_State;

	bool init(const AppConfig& config) {
		s_State.config = config;

		// 1. Modulus Init (Starts Core, Platform, and Audio)
		s_State.context = std::make_unique<modulus::Context>(modulus::InitFlags::Everything);
		if (!s_State.context->is_valid()) return false;

		// 2. Window Creation
		modulus::platform::WindowConfig winConfig;
		winConfig.title = config.title;
		winConfig.width = config.width;
		winConfig.height = config.height;
		winConfig.vsync = config.vsync;

		s_State.window = modulus::platform::create_window(winConfig);
		if (!s_State.window) return false;

		// 3. Modulus Graphics Init
		if (!modulus::gfx::init()) return false;

		// 4. ECS & Engine Init
		s_State.registry = std::make_unique<Registry>();
		me::Renderer::init();

		MOD_INFO("Mini Engine Initialized.");
		s_State.running = true;
		return true;
	}

	void run(Application& app, const AppConfig& config) {
		// 1. Initialize System
		if (!init(config)) {
			MOD_FATAL("Engine failed to initialize!");
			return;
		}

		// 2. User Start
		app.on_start(config.width, config.height);

		// 3. Create Timer
		modulus::core::Timer frame_timer;

		// 4. Main Loop
		double accumulator = 0.0;
		int frames = 0;

		int last_width = s_State.config.width;
		int last_height = s_State.config.height;

		while (s_State.running && s_State.window->update()) {
			// Delta Time
			float dt = frame_timer.elapsed();
			frame_timer.reset();

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

			// -- Handle Resizing --
			int current_width = s_State.window->width();
			int current_height = s_State.window->height();

			if (current_width != last_width || current_height != last_height) {
				modulus::gfx::set_viewport(0, 0, current_width, current_height);
				app.on_resize(current_width, current_height);

				last_width = current_width;
				last_height = current_height;
			}

			// -- Update Game --
			app.on_update(dt);

			// -- Render --
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