cmake_minimum_required(VERSION 3.10)
project(TestProject)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "test/*.cpp")

add_executable(test_app ${SOURCES})
