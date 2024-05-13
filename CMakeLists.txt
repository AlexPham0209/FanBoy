cmake_minimum_required(VERSION 3.8)
project("GameBoy")

set(CMAKE_CXX_STANDARD 20)

#Add SDL2 library
find_package(SDL2 REQUIRED)
include_directories(GameBoy ${SDL2_INCLUDE_DIRS})

#Iterates through all source and header files in src folder than add them to executable
file(GLOB_RECURSE SRC_FILE "src/*.cpp")
add_executable(GameBoy ${SRC_FILE})

#Link SDL2 libraries to build 
target_link_libraries(GameBoy ${SDL2_LIBRARIES})