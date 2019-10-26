cmake_minimum_required(VERSION 3.15)
project(demon)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(demon src/main.c src/daemon.c)
target_link_libraries(demon bass)