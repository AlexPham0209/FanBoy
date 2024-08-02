file(GLOB_RECURSE GAMEBOY_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(GameBoy STATIC ${GAMEBOY_SRC})
target_include_directories(GameBoy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})