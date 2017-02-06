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

<<<<<<< develop
# Create executable that links the source code, unit test, header file, and Boost.
add_executable(exe ${src} ${test})
target_link_libraries(exe ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
=======
include_directories(src)

# Add source files
set(src
  src/Networking/Request.cpp
  src/Networking/Response.cpp
  src/Networking/Tcp/EventArgs.cpp
  src/Networking/Tcp/Socket.cpp
  src/Networking/Tcp/Listener.cpp
  src/Core/Application.cpp
  src/Event/Observable.cpp
  src/Event/Observer.cpp
  src/Logging/LogEventArgs.cpp
  src/Logging/TcpLogger.cpp
  src/Threading/Cond.cpp
  src/Threading/Mutex.cpp
  src/Threading/Thread.cpp
  src/UI/Console.cpp
  src/Utilities/String.cpp
)

add_library(${project_name_shared_lib} SHARED src/Core/Application.cpp)
add_library(${project_name_lib} src/Core/Application.cpp)
add_executable(${project_name} src/main.cpp ${src})

target_link_libraries(${project_name} ${project_name_lib} pthread)

include_directories(lib/catch)
>>>>>>> local

# Add support for unit tests e.g. ctest.
enable_testing()
add_test(myTest exe)
