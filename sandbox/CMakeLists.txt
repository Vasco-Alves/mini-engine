add_executable(sandbox src/main.cpp)

# Link to your Engine (which transitively links Modulus)
target_link_libraries(sandbox PRIVATE mini_engine)

# Copy assets to build directory (Optional, but useful)
# file(COPY "${CMAKE_SOURCE_DIR}/assets" DESTINATION "${CMAKE_BINARY_DIR}")