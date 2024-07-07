cmake_minimum_required(VERSION 3.29)

project(Eldorado CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 23)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE
	src/main.cpp
)