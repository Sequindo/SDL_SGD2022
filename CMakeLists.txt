cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(SGD_proj VERSION 0.1.0)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB_RECURSE SGD_proj_SOURCES "src/*.cpp")
add_executable(SGD_proj ${SGD_proj_SOURCES})
target_include_directories(SGD_proj PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(SGD_proj ${SDL2_LIBRARIES})
