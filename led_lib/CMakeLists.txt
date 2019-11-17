cmake_minimum_required(VERSION 3.5)

project(led)

set(CMAKE_CXX_STANDARD 17)

file(GLOB rpi_SRC
        "../*.c"
        )

add_executable(led test.cpp ${rpi_SRC})
