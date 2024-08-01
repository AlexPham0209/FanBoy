cmake_minimum_required(VERSION 3.8)

file(GLOB_RECURSE SRC_FILES "*.cpp")
add_executable(GameBoyApp ${SRC_FILES})
target_link_libraries(GameBoyApp PUBLIC GameBoy Imgui NativeFileDialog ${SDL2_LIBRARIES})