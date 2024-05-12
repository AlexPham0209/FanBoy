cmake_minimum_required(VERSION 3.8)
project("GameBoy")

set(CMAKE_CXX_STANDARD 20)
find_package(SDL2 REQUIRED)
include_directories(SDL2Test ${SDL2_INCLUDE_DIRS})

file(GLOB_RECURSE SRC_FILE "src/*.cpp" "src/*.h")
add_executable(GameBoy ${SRC_FILE})

target_link_libraries(GameBoy ${SDL2_LIBRARIES})
