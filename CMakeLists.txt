cmake_minimum_required(VERSION 3.4)
project(COL333Assignment1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp State.h State.cpp Problem.h Search.h Problem.cpp Search.cpp node.h)
add_executable(COL333Assignment1 ${SOURCE_FILES})