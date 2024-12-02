cmake_minimum_required(VERSION 3.13)
project(Core)
set(CMAKE_CXX_STANDARD 23)

set(SOURCE_FILES Test.h Test.cpp)

add_library(Core STATIC ${SOURCE_FILES})

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})