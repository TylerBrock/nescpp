cmake_minimum_required(VERSION 3.1)

project(nes)

add_definitions(-std=c++1y)

add_library(nescore
    cpu.cpp
    memory.cpp
)

#add_executable(nes nes.cpp)
#target_link_libraries(nes nescore)

add_executable(test_nes test.cpp)
target_link_libraries(test_nes nescore)
