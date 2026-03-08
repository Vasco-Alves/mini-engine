# Automatically find all cpp and hpp files in sandbox
file(GLOB_RECURSE SANDBOX_SOURCES "src/*.cpp" "include/*.hpp")

# Create executable with all found files
add_executable(sandbox ${SANDBOX_SOURCES})

# Link to your Engine (which transitively links Modulus, mini-ecs, GLM, etc)
target_link_libraries(sandbox PRIVATE mini_engine)

# Tell the sandbox where its own headers are
target_include_directories(sandbox PRIVATE "include")

# Copy assets to build directory (Optional, but useful)
# Run a copy command EVERY time the sandbox finishes building
add_custom_command(TARGET sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:sandbox>/assets"
)
