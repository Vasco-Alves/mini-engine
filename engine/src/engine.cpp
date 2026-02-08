#include <mini-engine/engine.hpp>

// Modulus Includes
#include <modulus/core/context.hpp>
#include <modulus/platform/platform.hpp>
#include <modulus/gfx/graphics.hpp>
#include <modulus/core/log.hpp>

#include <memory>

namespace me {

    struct EngineState {
        std::unique_ptr<modulus::Context> context;
        std::unique_ptr<modulus::platform::IWindow> window;
        bool running = false;
    };

    static EngineState s_State;

    bool init(const EngineConfig& config) {
        // 1. Create Context (Init Core & Platform)
        s_State.context = std::make_unique<modulus::Context>();
        if (!s_State.context->is_valid()) {
            return false;
        }

        // 2. Create Window
        modulus::platform::WindowConfig winConfig;
        winConfig.title = config.title;
        winConfig.width = config.width;
        winConfig.height = config.height;
        
        s_State.window = modulus::platform::create_window(winConfig);
        if (!s_State.window) return false;

        // 3. Init Graphics
        if (!modulus::gfx::init()) return false;

        MOD_INFO("Mini Engine Initialized Successfully!");
        s_State.running = true;
        return true;
    }

    void run() {
        while (s_State.running && s_State.window->update()) {
            
            // Render Loop
            modulus::gfx::clear({ 0.1f, 0.1f, 0.12f, 1.0f }); // Nice dark blue

            // [Future: Render your Scene here]

            modulus::gfx::present(*s_State.window);
        }
    }

    void shutdown() {
        s_State.window.reset();
        s_State.context.reset();
        MOD_INFO("Mini Engine Shutdown.");
    }
}