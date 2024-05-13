cmake_minimum_required(VERSION 3.8)
project("GameBoy")

set(CMAKE_CXX_STANDARD 20)

enable_testing()
add_subdirectory(app)
add_subdirectory(src)
add_subdirectory(lib/googletest)
add_subdirectory(testing)
