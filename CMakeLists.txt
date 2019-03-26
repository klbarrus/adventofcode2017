cmake_minimum_required(VERSION 3.1...3.14)
if (${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(AdventOfCode2017
  VERSION 1.0
  DESCRIPTION "Advent of Code 2017, in C++"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(2017-01 2017-01.cpp)
add_executable(2017-02 2017-02.cpp)
add_executable(2017-03 2017-03.cpp)
add_executable(2017-04 2017-04.cpp)
add_executable(2017-05 2017-05.cpp)
add_executable(2017-06 2017-06.cpp)
