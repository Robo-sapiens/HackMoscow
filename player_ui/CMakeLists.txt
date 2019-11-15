cmake_minimum_required(VERSION 3.10)

project(player_ui LANGUAGES CXX)

## set up variables
set(CMAKE_CXX_STANDARD 17)
set(ROOT ..)
set(LIB ../lib)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## include directories
include_directories(${LIB})
include_directories(styles)
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

## ui requirements
set(CMAKE_CXX_FLAGS "-DWITH_GUI")
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(UI_DIR .)
set(UI_SRC
        ${UI_DIR}/main.cpp
        ${UI_DIR}/main_window.cpp
        ${UI_DIR}/main_window.h
        ${UI_DIR}/main_window.ui
        ${UI_DIR}/player_threads.cpp
        ${UI_DIR}/player_threads.h
        ${UI_DIR}/devices.cpp
        ${UI_DIR}/devices.h
        ${UI_DIR}/devices.ui
        ${UI_DIR}/color.cpp
        ${UI_DIR}/color.h
        ${UI_DIR}/color.ui
        ${UI_DIR}/animation.cpp
        ${UI_DIR}/animation.ui
        ${UI_DIR}/animation.h
        ${UI_DIR}/device_interface.cpp
        ${UI_DIR}/device_interface.h
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
