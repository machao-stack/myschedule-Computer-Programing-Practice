cmake_minimum_required(VERSION 3.10)
project(myschedule)

set(CMAKE_CXX_STANDARD 17)

add_executable(myschedule main.cpp src/Task.cpp)

target_include_directories(myschedule PRIVATE include)
