cmake_minimum_required(VERSION 2.8)

set(project_name cpp98posix)
set(project_name_test ${project_name}_test)
set(project_name_lib ${project_name}_lib)
set(project_name_shared_lib ${project_name}_slib)
set(CMAKE_BUILD_TYPE Release)

project(${project_name})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_definitions(-std=c++11 -stdlib=libc++ -O3 -Wall)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_definitions(-std=c++11 -O3 -Wall)
endif()

include_directories(src)

# Add source files
set(src
  src/Communication/Request.cpp
  src/Communication/TcpEventArgs.cpp
  src/Communication/TcpSocket.cpp
  src/Core/Application.cpp
  src/Event/Observable.cpp
  src/Event/Observer.cpp
  src/Logging/LogEventArgs.cpp
  src/Logging/TcpLogger.cpp
  src/Threading/Cond.cpp
  src/Threading/Mutex.cpp
  src/Threading/Thread.cpp
  src/Threading/ThreadManager.cpp
  src/UI/Console.cpp
  src/Utilities/String.cpp
)

add_library(${project_name_shared_lib} SHARED src/Core/Application.cpp)
add_library(${project_name_lib} src/Core/Application.cpp)
add_executable(${project_name} src/main.cpp ${src})

target_link_libraries(${project_name} ${project_name_lib} pthread)

add_library(Catch INTERFACE)
include_directories(lib/catch)

enable_testing()

add_executable(${project_name_test} test/main.cpp)
target_link_libraries(${project_name_test} ${project_name_lib} Catch pthread)

add_test(Utilities::String ${project_name_test})
