cmake_minimum_required(VERSION 3.5)

project(player)
## set up variables
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -g)

## include directories
include_directories(lib)
include_directories(lib/LED)
include_directories(lib/player)
include_directories(lib/rpi_ws281x)
include_directories(lib/serial)
include_directories(lib/uart)

## out directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY out)

## serial lib
add_library(serial STATIC lib/serial/serial.cpp)
add_library(uart STATIC lib/uart/uart.cpp)
target_link_libraries(uart ${CMAKE_THREAD_LIBS_INIT})

## thread support
find_package(Threads)

## my_rpi
file(GLOB rpi_SRC
        "lib/rpi_ws281x/*.c"
        )
add_library(rpi_led ${rpi_SRC})

## LED
add_library(LED STATIC lib/LED/LED.cpp)
target_link_libraries(LED rpi_led)

## player
add_library(player STATIC lib/player/player.cpp lib/player/polygon.cpp lib/player/fixed_queue.h)
target_link_libraries(player serial ${CMAKE_THREAD_LIBS_INIT} LED uart)

## main
add_executable(player_usage src/main.cpp)
target_link_libraries(player_usage player)
