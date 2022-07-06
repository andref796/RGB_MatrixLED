cmake_minimum_required(VERSION 3.22)
project(rgb)

set(CMAKE_CXX_STANDARD 11)

add_executable(rgb main.cpp i2c.cpp i2c.h)
target_link_libraries(rgb i2c)