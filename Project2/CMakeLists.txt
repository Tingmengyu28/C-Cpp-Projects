cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

project(pro2)

add_executable(demo main.cpp cal.cpp formula.cpp)
