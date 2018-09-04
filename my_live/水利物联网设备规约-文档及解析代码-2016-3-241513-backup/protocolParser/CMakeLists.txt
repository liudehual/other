project(protocolParser)
cmake_minimum_required(VERSION 2.8)
set( CMAKE_C_COMPILER gcc)
set(SRC_LIST
	main.c
	protocolParser.c
	helper.c
	)
include_directories(".")
add_executable(${PROJECT_NAME} ${SRC_LIST})

