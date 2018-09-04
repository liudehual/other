cmake_minimum_required(VERSION 2.8)

project(AAC-Viewer)
set(SRC_LIST
     main.cpp
     AACPacket.cpp
     AACParser.cpp
)
add_executable(${PROJECT_NAME} ${SRC_LIST})
