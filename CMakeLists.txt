cmake_minimum_required(VERSION 3.20)
project(par_DPLL)

set(CMAKE_CXX_STANDARD 20)

include_directories("." "tests")

add_executable(par_DPLL main.cpp)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(par_DPLL PRIVATE -O3)
endif (CMAKE_BUILD_TYPE STREQUAL "Release")
if (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    target_compile_options(par_DPLL PRIVATE -O3)
endif (CMAKE_BUILD_TYPE STREQUAL "Release")
