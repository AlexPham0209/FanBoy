cmake_minimum_required(VERSION 3.8)

file(GLOB_RECURSE IMGUI_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(Imgui STATIC ${IMGUI_SRC})
message(${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
