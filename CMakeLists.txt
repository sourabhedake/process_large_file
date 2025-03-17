cmake_minimum_required(VERSION 3.10)
project(MultiThreadedLargeFileProcessor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(large_file_processor main.cpp)
