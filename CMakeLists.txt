cmake_minimum_required(VERSION 3.1)

project(nes)

add_definitions(-std=c++1y)

add_executable(nes
    cpu.cpp
    memory.cpp
)
