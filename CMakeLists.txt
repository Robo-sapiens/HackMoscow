cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME demon)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
include_directories(test)

## set up variables
set(ROOT ${PROJECT_SOURCE_DIR})

## Ardulib
add_library(ardu STATIC test/arduino_serial.cpp)

## Thread support
find_package(Threads)

add_executable(${PROJECT_NAME} test/parec.cpp)

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME} pulse pulse-simple fftw3 ardu)