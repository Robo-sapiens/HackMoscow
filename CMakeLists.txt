cmake_minimum_required(VERSION 3.5)

project(player)
## set up variables
set(CMAKE_CXX_STANDARD 17)
set(ROOT ${PROJECT_SOURCE_DIR})
set(LIB ${PROJECT_SOURCE_DIR}/lib)

## include directories
include_directories(${LIB})
include_directories(${LIB}/player)
include_directories(${LIB}/serial)
#include_directories(${LIB}/pulse_device)
#include_directories(${LIB}/pulse_capture)
include_directories(${LIB}/LED)
include_directories(${LIB}/bass)
include_directories(${LIB}/alsa_cap)

## out directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROOT}/out)

## serial lib
add_library(talker STATIC ${LIB}/serial/serial.cpp)

## thread support
find_package(Threads)

### pulseaudio lib
#find_path(PULSEAUDIO_INCLUDE_DIR NAMES pulse/pulseaudio.h)
#find_library(PULSEAUDIO_LIBRARY NAMES pulse)
#
### pulseaudio device parsing
#add_library(pulse_device STATIC ${LIB}/pulse_device/list_devices.cpp)
#target_link_libraries(pulse_device pulse)
#
### pulseaudio capture
#add_library(pulse_capture STATIC ${LIB}/pulse_capture/capture.cpp)
#target_link_libraries(pulse_capture pulse_device pulse-simple pulse)

## alsa record
find_path(ALSA_INCLUDE_DIR NAMES alsa/asoundlib.h)
find_library(ALSA_LIBRARY NAMES asound)
add_library(alsa_cap STATIC ${LIB}/alsa_cap/capture.cpp)
target_link_libraries(alsa_cap asound)

## LED
add_library(LED STATIC ${LIB}/LED/LED.cpp)
target_link_libraries(LED ${LIB}/rpi_ws281x/libws2811.a)

## player
add_library(player STATIC ${LIB}/player/player.cpp)
target_link_libraries(player talker ${CMAKE_THREAD_LIBS_INIT} alsa_cap LED)
target_link_libraries(player ${LIB}/bass/hardfp/libbass.so)

## main
add_executable(player_usage src/main.cpp)
target_link_libraries(player_usage player)

#
add_executable(alsa_usage alsa/alsa_cap.cpp)
target_link_libraries(alsa_usage asound)
