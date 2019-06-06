cmake_minimum_required(VERSION 3.6)

set (CMAKE_CXX_STANDARD 11)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra ")

project(PI VERSION 0.1.0)

add_executable(PI  main.cpp
                run.cpp
                run.hpp
                utils.cpp
                utils.hpp)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

# target_include_directories(${PROJECT_NAME} PUBLIC dep)
target_compile_options(${PROJECT_NAME} PUBLIC  -Wl,--gc-sections -Wl,--strip-all)
