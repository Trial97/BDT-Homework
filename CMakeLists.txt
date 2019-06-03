cmake_minimum_required(VERSION 3.13)

set (CMAKE_CXX_STANDARD 17)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra ")

project(PI VERSION 0.1.0)

add_executable(PI)

function(target_sources_local target)
    cmake_policy(PUSH)
    cmake_policy(SET CMP0076 NEW)
    target_sources(${target} ${ARGN})
    cmake_policy(POP)
    return()
endfunction()

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(PI PUBLIC OpenMP::OpenMP_CXX)
endif()

# target_include_directories(${PROJECT_NAME} PUBLIC dep)
target_compile_options(${PROJECT_NAME} PUBLIC  -Wl,--gc-sections -Wl,--strip-all  )
target_sources(PI 
	PUBLIC
		main.cpp
		run.cpp
		run.hpp
		utils.cpp
		utils.hpp
		)


