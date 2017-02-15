cmake_minimum_required(VERSION 2.8)

set(project_name cpp98posix)
set(project_name_test ${project_name}_test)
set(project_name_lib ${project_name})
set(CMAKE_BUILD_TYPE Release)

option(BuildShared "BuildShared" ON)
option(BuildTests "BuildTests" OFF)

if(BuildShared)
  set(StaticOrShared "SHARED")
  add_definitions(-DFRAMEWORK_EXPORT)
else(BuildShared)
  set(StaticOrShared "STATIC")
endif(BuildShared)

project(${project_name})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_definitions(-std=c++11 -stdlib=libc++ -O3 -Wall)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_definitions(-std=c++0x -O3 -Wall)
endif()

# Add header files
set(headers
  src/Collections/Dictionary.h
  src/Collections/List.h
  src/Networking/Host.h
  src/Networking/IListener.h
  src/Networking/ISocket.h
  src/Networking/Request.h
  src/Networking/Response.h
  src/Networking/Tcp/EventArgs.h
  src/Networking/Tcp/Listener.h
  src/Networking/Tcp/Socket.h
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
  src/Threading/Cond.h
  src/Threading/IThread.h
  src/Threading/Mutex.h
  src/Threading/Queue.h
  src/Threading/Thread.h
  src/UI/Console.h
  src/Utilities/String.h
)

# Add source files
set(sources
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

include_directories(src)

add_library(${project_name_lib} ${StaticOrShared} ${sources} ${header})
#add_executable(${project_name} src/main.cpp ${sources})

#target_link_libraries(${project_name} ${project_name_lib} pthread)

install(TARGETS ${project_name_lib}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION bin
  ARCHIVE DESTINATION lib
)
install(FILES ${headers} DESTINATION include/${project_name})

if(BuildTests)
  include_directories(lib/catch)

  enable_testing()

  add_executable(${project_name_test} test/main.cpp)
  target_link_libraries(${project_name_test} ${project_name_lib} pthread)

  add_test(Utilities::String ${project_name_test})
endif()
