cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME player)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD "17")

## set up variables
set(ROOT ${PROJECT_SOURCE_DIR})
set(LIB ${PROJECT_SOURCE_DIR}/lib)

## Out directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROOT}/out)

## include directories
include_directories(${ROOT}/include)
#include_directories(${ROOT}/lib)

## srcs
add_executable(${PROJECT_NAME} src/main.cpp src/player.cpp)

target_link_libraries(player bass)