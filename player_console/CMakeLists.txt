cmake_minimum_required(VERSION 3.5)

project(player)
## set up variables
set(CMAKE_CXX_STANDARD 17)
set(ROOT ..)
set(LIB ../lib)

## include directories
include_directories(${LIB})
include_directories(ui)
include_directories(${LIB}/player)
include_directories(${LIB}/serial)
include_directories(${LIB}/pulse_device)
include_directories(${LIB}/pulse_capture)

## out directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROOT}/out)

## serial lib
add_library(talker STATIC ${LIB}/serial/serial.cpp)

## thread support
find_package(Threads)

## pulseaudio lib
find_path(PULSEAUDIO_INCLUDE_DIR NAMES pulse/pulseaudio.h)
find_library(PULSEAUDIO_LIBRARY NAMES pulse)

## pulseaudio device parsing
add_library(pulse_device STATIC ${LIB}/pulse_device/list_devices.cpp)
target_link_libraries(pulse_device pulse)

## pulseaudio capture
add_library(pulse_capture STATIC ${LIB}/pulse_capture/capture.cpp)
target_link_libraries(pulse_capture pulse_device pulse-simple pulse)

## player
add_library(player STATIC ${LIB}/player/player.cpp)
target_link_libraries(player bass talker ${CMAKE_THREAD_LIBS_INIT} pulse_capture)

## main console
add_executable(player_usage main.cpp)
target_link_libraries(player_usage player)
