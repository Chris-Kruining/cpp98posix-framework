cmake_minimum_required(VERSION 2.8)
project(ChrisPP)
set(CMAKE_BUILD_TYPE Debug)

# Add source files
file(GLOB src
  src/*.cpp
  src/*.h
)

add_library(chrispp SHARED src/Core/Application.cpp)
