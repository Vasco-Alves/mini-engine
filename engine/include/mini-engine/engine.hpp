#pragma once

#include <string>

namespace me {

    struct EngineConfig {
        std::string title = "Mini Engine App";
        int width = 1280;
        int height = 720;
    };

    // Initialize Modulus, Window, and Context
    bool init(const EngineConfig& config);

    // Run the main loop
    void run();

    // Cleanup
    void shutdown();

}