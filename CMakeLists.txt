﻿cmake_minimum_required(VERSION 3.8)
project("GameBoy")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

#set(SDL2_PATH "C:\Users\RedAP\Documents\C++ Libraries\SDL2-2.30.4")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

enable_testing()
add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(app)