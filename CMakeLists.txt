cmake_minimum_required(VERSION 3.16)
project(rgb)

set(CMAKE_CXX_STANDARD 11)

add_executable(rgb main.cpp MatrixLed.cpp MatrixLed.h)
target_link_libraries(rgb i2c)
