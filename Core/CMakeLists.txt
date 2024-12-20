cmake_minimum_required(VERSION 3.27)
project(Core)
set(CMAKE_CXX_STANDARD 23)

set(IMGUI_FILES
        src/imgui/fs_ocornut_imgui.bin.h
        src/imgui/vs_ocornut_imgui.bin.h
        src/imgui/imgui_impl_bgfx.h
        src/imgui/imgui_impl_bgfx.cpp
        Libs/imgui.cmake/imgui/backends/imgui_impl_glfw.cpp
        Libs/imgui.cmake/imgui/backends/imgui_impl_glfw.h
)

set(SOURCE_FILES
        src/Graphics/Renderer.h
        src/Graphics/Renderer.cpp
        src/Engine.h
        src/Engine.cpp
        src/Project.h
        src/Scene/Scene.cpp
        src/Scene/Scene.h
)

add_library(Core STATIC ${SOURCE_FILES} ${IMGUI_FILES})

# GLFW
add_subdirectory(Libs/glfw)
target_link_libraries(Core PRIVATE glfw)
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Libs/glfw/include)

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
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Libs/bgfx.cmake/bx/include/compat/mingw)

# ImGui
add_subdirectory(Libs/imgui.cmake)
target_link_libraries(Core PRIVATE imgui.cmake)