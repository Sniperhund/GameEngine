cmake_minimum_required(VERSION 3.27)
project(Editor)
set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

add_executable(Editor ${SOURCES})

target_link_libraries(Editor Core)