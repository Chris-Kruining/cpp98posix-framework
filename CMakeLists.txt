cmake_minimum_required(VERSION 2.8)
project(myProject)

# Add source code and setup folder structure.
file(GLOB src
  src/*.cpp
  src/*.h
)
set(test test/Core/Application.test.cpp)

# Add Boost unit test library.
set(Boost_USE_STATIC_LIBS on)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# Add C++98 compiler flags.
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_definitions(-std=c++98 -stdlib=libc++ -O3 -Wall)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_definitions(-std=c++98 -O3 -Wall)
endif()

# Create executable that links the source code, unit test, header file, and Boost.
add_executable(exe ${src} ${test})
target_link_libraries(exe ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

# Add support for unit tests e.g. ctest.
enable_testing()
add_test(myTest exe)
