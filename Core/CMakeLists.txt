cmake_minimum_required(VERSION 3.27)
project(Core)
set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCE_FILES "src/*.h" "src/*.cpp")

add_library(Core STATIC ${SOURCE_FILES})

# GLFW
add_subdirectory(Libs/glfw)
target_link_libraries(Core PRIVATE glfw)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(Core PRIVATE OpenGL::GL)

# BGFX

# There's a bug in bgfx where multithreading doesn't work on MacOS
if (APPLE)
    set(BGFX_CONFIG_MULTITHREADED OFF)
endif()

add_subdirectory(Libs/bgfx.cmake)
target_link_libraries(Core PRIVATE bgfx)
target_include_directories(Core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Libs/bgfx.cmake/bgfx/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Libs/bgfx.cmake/bx/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Libs/bgfx.cmake/bimg/include
)

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
