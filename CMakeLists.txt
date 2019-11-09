cmake_minimum_required(VERSION 3.5)

## set up variables
set(PROJECT_NAME demon)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)
set(ROOT ${PROJECT_SOURCE_DIR})
include_directories(include)

project(${PROJECT_NAME})

## Thread support
find_package(Threads)

## ardu lib
set(ARDU_SRC src/arduino_serial.cpp)
add_library(talker STATIC ${ARDU_SRC})

## pulseaudio lib
find_path(PULSEAUDIO_INCLUDE_DIR NAMES pulse/pulseaudio.h)
find_library(PULSEAUDIO_LIBRARY NAMES pulse)

## target
add_executable(${PROJECT_NAME}
        src/parec.cpp
#        src/pulse_utils.cpp
#        include/pulse_utils.h
        )
target_link_libraries(demon fftw3 pulse-simple pulse talker ${CMAKE_THREAD_LIBS_INIT})


find_path(ALSA_INCLUDE_DIR NAMES alsa/asoundlib.h)
find_library(ALSA_LIBRARY NAMES asound)

add_executable(alsal src/pulse_utils.cpp)
target_link_libraries(alsal asound)