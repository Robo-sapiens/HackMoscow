cmake_minimum_required(VERSION 3.13)
project(test_talker)

set(CMAKE_CXX_STANDARD 17)
set(SRC src/arduino_serial.cpp)

add_library(talker STATIC ${SRC})
include_directories(include)
find_package(Threads)

#   main program
add_executable(test_talker src/main.cpp)
target_link_libraries(test_talker talker)
