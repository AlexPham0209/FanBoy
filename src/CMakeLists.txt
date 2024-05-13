cmake_minimum_required(VERSION 3.8)

file(GLOB_RECURSE SRC_FILES "*.cpp")
file(GLOB_RECURSE HEADER_FILES "*.h")
add_library(GameBoy STATIC ${SRC_FILES} ${HEADER_FILES})