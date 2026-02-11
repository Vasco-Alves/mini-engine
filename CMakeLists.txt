cmake_minimum_required(VERSION 3.20)

# Initialize Project with Vcpkg Toolchain support
project(
    "mini-engine"
    VERSION 0.2.2
    DESCRIPTION "A simple game engine using the modulus framework"
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==============================================================================
# 1. Dependencies (Provided by Vcpkg)
# ==============================================================================
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# Compatibility: Modulus looks for 'glfw', but vcpkg gives 'glfw3::glfw'
if(TARGET glfw3::glfw)
    add_library(glfw ALIAS glfw3::glfw)
endif()

# ==============================================================================
# 2. Add Modulus (The Framework)
# ==============================================================================
# This will build Modulus, using the GLFW we just found above.
add_subdirectory(vendor/modulus)

# ==============================================================================
# 3. Build Engine & Sandbox
# ==============================================================================
add_subdirectory(engine)
add_subdirectory(sandbox)