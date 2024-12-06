cmake_minimum_required(VERSION 3.27)
project(GameEngine)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(Core)
add_subdirectory(Runtime)
add_subdirectory(Editor)