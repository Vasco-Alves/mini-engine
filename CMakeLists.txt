cmake_minimum_required(VERSION 3.20)

project(
    "mini-engine"
    VERSION 0.2.2
    DESCRIPTION "A simple game engine using the modulus framework"
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Dependencies (Provided by Vcpkg)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# Compatibility: Modulus looks for 'glfw', but vcpkg gives 'glfw3::glfw'
if(TARGET glfw3::glfw)
    add_library(glfw ALIAS glfw3::glfw)
endif()

# 2. Add Modulus
# This will build Modulus, using the GLFW we just found above.
add_subdirectory(vendor/modulus)

# 3. Add ECS library
add_subdirectory(vendor/mini-ecs)

# 4. Build Engine & Sandbox
add_subdirectory(engine)

# If this is the top-level project, build the sandbox.
# If someone included us as a submodule, CMAKE_SOURCE_DIR will be their game folder, so we skip building the sandbox!
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    add_subdirectory(sandbox)
endif()