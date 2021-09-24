cmake_minimum_required(VERSION 3.17)
project(Hukan-Core)

include_directories(../..)
include_directories(src)
include_directories(src/Hukan)

add_subdirectory(src)

add_executable(Hukan-Example
    examples/Example.cpp
)

target_link_libraries(Hukan-Example Hukan)