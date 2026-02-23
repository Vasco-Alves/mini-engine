file(GLOB_RECURSE ENGINE_SOURCES "src/*.cpp" "include/*.hpp")

add_library(mini_engine ${ENGINE_SOURCES})

# Include Paths
target_include_directories(mini_engine PUBLIC 
    "include"
)

# This gives us access to modulus::*, glm::*, and mini-ecs::*
target_link_libraries(mini_engine PUBLIC 
    modulus::modulus 
    glm::glm
    mini-ecs
)