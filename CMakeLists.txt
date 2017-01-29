cmake_minimum_required(VERSION 2.8)
project(ChrisPP)
set(CMAKE_BUILD_TYPE Debug)

#add_library(chrispp SHARED src/Core/Application.cpp)

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

# Add test files
set(test
  test/Communication/TcpSocket.test.cpp
  test/Core/Application.test.cpp
)

find_package (Threads)

set(Boost_USE_STATIC_LIBS on)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_definitions(-pedantic -ggdb -std=c++98 -stdlib=libc++ -O3 -Wall)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_definitions(-pedantic -ggdb -std=c++98 -O3 -Wall)
endif()

message(${src})
message(${test})

add_executable(exe ${src} ${test})
target_link_libraries(exe ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
  target_compile_options(PUBLIC exe "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
  target_link_libraries(exe "${CMAKE_THREAD_LIBS_INIT}")
endif()

enable_testing()
add_test(myTest exe)
