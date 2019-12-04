cmake_minimum_required(VERSION 3.5)
project(Traceroute VERSION 1.0.191124)

# COMPILER
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unknown-pragmas")

# SOURCES
include_directories(include)
set(SOURCES
    src/IPAddress.cpp
    src/ICMPReceiver.cpp
    src/ICMPSender.cpp
    src/ICMPController.cpp
    src/traceroute.cpp)

# OUTPUT
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
add_executable(traceroute ${SOURCES})
