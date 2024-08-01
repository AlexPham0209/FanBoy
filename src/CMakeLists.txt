cmake_minimum_required(VERSION 3.8)

file(GLOB_RECURSE SRC_FILES "*.cpp")
add_library(GameBoy STATIC ${SRC_FILES})
target_include_directories(GameBoy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})