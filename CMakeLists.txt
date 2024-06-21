cmake_minimum_required(VERSION 3.8)
project("GameBoy")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

enable_testing()
add_subdirectory(app)
add_subdirectory(src)
