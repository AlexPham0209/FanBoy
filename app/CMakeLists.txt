cmake_minimum_required(VERSION 3.8)

find_package(SDL2 REQUIRED)
include_directories(GameBoyTests ${SDL2_INCLUDE_DIRS})

file(GLOB_RECURSE SRC_FILES "*.cpp")
add_executable(GameBoyApp ${SRC_FILES})
target_link_libraries(GameBoyApp PUBLIC GameBoy ${SDL2_LIBRARIES})