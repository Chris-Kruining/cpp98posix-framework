cmake_minimum_required(VERSION 2.8)

option(test "Build all tests." OFF)

set(project_name CppFramework)
set(project_name_test ${project_name}Test)
set(project_name_lib ${project_name}Lib)
set(project_name_shared_lib ${project_name}SharedLib)
set(CMAKE_BUILD_TYPE Test)

project(${project_name})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_definitions(-std=c++98 -stdlib=libc++ -O3 -Wall)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_definitions(-std=c++98 -O3 -Wall)
endif()

add_library(${project_name_shared_lib} SHARED src/Core/Application.cpp)
add_library(${project_name_lib} src/Core/Application.cpp)
add_executable(${project_name} src/main.cpp)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()

add_executable(${project_name_test} test/main.cpp)
target_link_libraries(${project_name_test} ${GTEST_LIBRARIES} pthread)

target_link_libraries(${project_name_test} ${project_name_lib})

add_test(Utilities::String ${project_name_test})
