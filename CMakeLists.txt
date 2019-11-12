cmake_minimum_required(VERSION 3.5)

project(demon)

set(CMAKE_CXX_STANDARD 17)
include_directories(test)

## Ardulib
add_library(ardu STATIC test/arduino_serial.cpp)

## Thread support
find_package(Threads)

## pulseaudio lib
find_path(PULSEAUDIO_INCLUDE_DIR NAMES pulse/pulseaudio.h)
find_library(PULSEAUDIO_LIBRARY NAMES pulse)

## pulseaudio device parsing
add_library(pulse_device STATIC test/list_devices.cpp)
target_link_libraries(pulse_device pulse)

##
add_executable(pulse_device_usage test/main.cpp)
target_link_libraries(pulse_device_usage pulse_device)