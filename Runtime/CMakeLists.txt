cmake_minimum_required(VERSION 3.13)
project(Runtime)
set(CMAKE_CXX_STANDARD 23)

set(SOURCE_FILES main.cpp)

add_subdirectory(Libs/Core)

add_executable(Runtime ${SOURCE_FILES})

target_link_libraries(Runtime Core)