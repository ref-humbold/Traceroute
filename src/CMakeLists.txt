cmake_minimum_required(VERSION 3.10)

# SOURCES
set(LIB_SOURCES
    "AppParameters.cpp"
    "EchoReply.cpp"
    "IcmpController.cpp"
    "Ip4Address.cpp"
    "SocketReceiver.cpp"
    "SocketSender.cpp")
set(EXE_SOURCES "traceroute.cpp")

# OUTPUT
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR})
add_library(${LIB_NAME} STATIC ${LIB_SOURCES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${EXE_OUTPUT_DIR}")
add_executable(${EXE_NAME} ${EXE_SOURCES})
target_link_libraries(${EXE_NAME} ${LIB_NAME})
