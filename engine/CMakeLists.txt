set(SOURCES
    "src/core/engine.cpp"
    "src/input/input.cpp"
    "src/render/renderer.cpp"
    "src/render/mesh.cpp"
)

add_library(mini_engine ${SOURCES})

# Include Paths
target_include_directories(mini_engine PUBLIC 
    "include"

    # --- SHORTCUT DIRECTORIES ---
    "include/mini-engine"
    "include/mini-engine/core"
    "include/mini-engine/ecs"
    "include/mini-engine/input"
    "include/mini-engine/render"
    "include/mini-engine/scene"
    "include/mini-engine/systems"
)

# This gives us access to modulus::*, glm::*, and mini-ecs::*
target_link_libraries(mini_engine PUBLIC 
    modulus::modulus 
    glm::glm
    mini-ecs
)