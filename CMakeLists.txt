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

# Add source files
set(src
  src/Collections/Dictionary.h
  src/Collections/List.h
  src/Communication/ISocket.h
  src/Communication/Request.h
  src/Communication/TcpEventArgs.h
  src/Communication/TcpSocket.h
  src/Core/Application.h
  src/Event/EventArgs.h
  src/Event/EventHandler.h
  src/Event/IEventArgs.h
  src/Event/IObservable.h
  src/Event/IObserver.h
  src/Event/Observable.h
  src/Event/Observer.h
  src/Logging/ILogger.h
  src/Logging/LogEventArgs.h
  src/Logging/TcpLogger.h
  src/Threading/IThread.h
  src/Threading/Thread.h
  src/Threading/ThreadData.h
  src/Threading/ThreadManager.h
  src/UI/Console.h
  src/Utilities/String.h
  src/Communication/Request.cpp
  src/Communication/TcpEventArgs.cpp
  src/Communication/TcpSocket.cpp
  src/Core/Application.cpp
  src/Event/Observable.cpp
  src/Event/Observer.cpp
  src/Logging/LogEventArgs.cpp
  src/Logging/TcpLogger.cpp
  src/Threading/Thread.cpp
  src/Threading/ThreadManager.cpp
  src/UI/Console.cpp
  src/Utilities/String.cpp
)

add_library(${project_name_shared_lib} SHARED src/Core/Application.cpp)
add_library(${project_name_lib} src/Core/Application.cpp)
add_executable(${project_name} src/main.cpp ${src})

target_link_libraries(${project_name} pthread)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()

add_executable(${project_name_test} test/main.cpp)
target_link_libraries(${project_name_test} ${GTEST_LIBRARIES} pthread)

target_link_libraries(${project_name_test} ${project_name_lib})

add_test(Utilities::String ${project_name_test})
