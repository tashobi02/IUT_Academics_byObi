cmake_minimum_required(VERSION 3.10)
project(vibe-cpu)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.hpp")

add_executable(vibe-cpu main.cpp ${SOURCES})
