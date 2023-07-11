cmake_minimum_required(VERSION 3.10)
project(Traceroute VERSION 2.0.230711)

# PROPERTIES
set(EXE_NAME traceroute)

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(OUTPUT_DIR "${PROJECT_SOURCE_DIR}/buildOut")
set(EXE_OUTPUT_DIR "${OUTPUT_DIR}/bin")

# COMPILER
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unknown-pragmas -O2")

# SOURCES
include_directories(${INCLUDE_DIR})

# OUTPUT
add_subdirectory(${SRC_DIR})
