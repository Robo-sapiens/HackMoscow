cmake_minimum_required(VERSION 3.10)

project(player_ui LANGUAGES CXX)

## set up variables
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## include directories
include_directories(lib)
include_directories(lib/player)
include_directories(lib/pulse_device)
include_directories(lib/pulse_capture)
include_directories(cmake-build-debug/player_ui_autogen/include)
include_directories(player_ui)

## thread support
find_package(Threads)

## pulseaudio lib
find_path(PULSEAUDIO_INCLUDE_DIR NAMES pulse/pulseaudio.h)
find_library(PULSEAUDIO_LIBRARY NAMES pulse)

## pulseaudio device parsing
add_library(pulse_device STATIC lib/pulse_device/list_devices.cpp)
target_link_libraries(pulse_device pulse)

## pulseaudio capture
add_library(pulse_capture STATIC lib/pulse_capture/capture.cpp)
target_link_libraries(pulse_capture pulse_device pulse-simple pulse)

## player
add_library(player STATIC lib/player/player.cpp lib/player/rgbparameters.cpp)
target_link_libraries(player bass ${CMAKE_THREAD_LIBS_INIT} pulse_capture)

## ui requirements
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(UI_SRC
        player_ui/main.cpp
        player_ui/main_window.cpp
        player_ui/main_window.h
        player_ui/main_window.ui
        player_ui/serial_thread.cpp
        player_ui/serial_thread.h
        player_ui/audio_thread.cpp
        player_ui/audio_thread.h
        player_ui/fft_thread.cpp
        player_ui/fft_thread.h
        player_ui/devices.cpp
        player_ui/devices.h
        player_ui/devices.ui
        player_ui/color.cpp
        player_ui/color.h
        player_ui/color.ui
        player_ui/animation.cpp
        player_ui/animation.ui
        player_ui/animation.h
        player_ui/polygon.cpp
        player_ui/polygon.h
        )

find_package(Qt5 COMPONENTS Widgets Core Gui SerialPort REQUIRED)

add_executable(player_ui ${UI_SRC})

target_link_libraries(player_ui
        player
        Qt5::Widgets
        Qt5::Core
        Qt5::Gui
        Qt5::SerialPort
        )
