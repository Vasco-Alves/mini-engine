#include <mini-engine/engine.hpp>

#include <iostream>

int main() {
    me::EngineConfig config;
    config.title = "My First Game";
    config.width = 1600;
    config.height = 900;

    if (!me::init(config)) {
        std::cerr << "Engine failed to initialize!" << std::endl;
        return -1;
    }

    me::run();

    me::shutdown();
    return 0;
}