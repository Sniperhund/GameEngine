cmake_minimum_required(VERSION 3.27)
project(Runtime)
set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCE_FILES "src/*.h" "src/*.cpp")

add_executable(Runtime ${SOURCE_FILES})

target_link_libraries(Runtime Core)