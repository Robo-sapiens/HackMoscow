cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME demon)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)

## set up variables
set(ROOT ${PROJECT_SOURCE_DIR})

## Thread support
#find_package(Threads)
## ardu lib
set(ARDU_SRC src/arduino_serial.cpp)
add_library(talker STATIC ${ARDU_SRC})

add_executable(${PROJECT_NAME} src/parec.cpp)


find_path(PULSEAUDIO_INCLUDE_DIR
        NAMES pulse/pulseaudio.h
        DOC "The PulseAudio include directory"
        )

find_library(PULSEAUDIO_LIBRARY
        NAMES pulse
        DOC "The PulseAudio library"
        )

target_link_libraries(demon fftw3 pulse-simple pulse talker)
set(CMAKE_CXX_FLAGS -pthread)