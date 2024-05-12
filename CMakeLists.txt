cmake_minimum_required(VERSION 3.8)
project("GameBoy")

set(CMAKE_CXX_STANDARD 20)
file(GLOB_RECURSE CPP_FILE "src/*.cpp")
add_executable(GameBoy ${CPP_FILE})
target_include_directories(GameBoy PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
