# Collect sources
file(GLOB_RECURSE ENGINE_SOURCES "src/*.cpp" "include/*.hpp")

add_library(mini_engine ${ENGINE_SOURCES})

# Include Paths
target_include_directories(mini_engine PUBLIC 
    "include"
)

# Link to Modulus
# This gives us access to modulus::core, modulus::gfx, modulus::platform
target_link_libraries(mini_engine PUBLIC 
    modulus::modulus 
    glm::glm
)