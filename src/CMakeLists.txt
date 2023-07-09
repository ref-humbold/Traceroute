cmake_minimum_required(VERSION 3.10)

# SOURCES
set(SOURCES
    "AppParameters.cpp"
    "IPv4Address.cpp"
    "ICMPController.cpp"
    "SocketReceiver.cpp"
    "SocketSender.cpp"
    "traceroute.cpp")

# OUTPUT
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${EXE_OUTPUT_DIR}")
add_executable(${EXE_NAME} ${SOURCES})
