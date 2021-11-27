cmake_minimum_required(VERSION 3.20)
project(par_DPLL)

set(CMAKE_CXX_STANDARD 20)

include_directories("." "tests")

add_executable(par_DPLL main.cpp)

include(FindOpenMP)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
else (OPENMP_FOUND)
    message("ERROR: OpenMP could not be found.")
endif (OPENMP_FOUND)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(par_DPLL PRIVATE -O3)
endif (CMAKE_BUILD_TYPE STREQUAL "Release")
if (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    target_compile_options(par_DPLL PRIVATE -O3)
endif (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
