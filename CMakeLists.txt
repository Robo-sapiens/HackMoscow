cmake_minimum_required(VERSION 3.5)

## set up variables
set(PROJECT_NAME demon)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)
set(ROOT ${PROJECT_SOURCE_DIR})
include_directories(pulse arduino_lib alsa)

project(${PROJECT_NAME})

## Thread support
find_package(Threads)

## ardu lib
set(SERIAL_SRC arduino_lib/arduino_serial.cpp)
add_library(talker STATIC ${SERIAL_SRC})

## pulseaudio lib
find_path(PULSEAUDIO_INCLUDE_DIR NAMES pulse/pulseaudio.h)
find_library(PULSEAUDIO_LIBRARY NAMES pulse)

## pulse record
add_executable(${PROJECT_NAME}
        pulse/parec.cpp
        pulse/fourier_processing.cpp
        pulse/serial_talker.cpp
        )
target_link_libraries(demon fftw3 pulse-simple pulse talker ${CMAKE_THREAD_LIBS_INIT})

## alsa record
find_path(ALSA_INCLUDE_DIR NAMES alsa/asoundlib.h)
find_library(ALSA_LIBRARY NAMES asound)
add_executable(alsa_rec alsa/alsa_cap.cpp)
target_link_libraries(alsa_rec asound)