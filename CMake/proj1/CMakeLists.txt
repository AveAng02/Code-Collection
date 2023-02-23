
cmake_minimum_required(VERSION 3.10) 

project(proj1 VERSION 1.0) 

add_executable(proj1 main.cxx) 

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(proj1Config.h.in proj1Config.h)

target_include_directories(proj1 PUBLIC 
			"${PROJECT_BINARY_DIR}"
			"${PROJECT_BINARY_DIR}/Mathlib")

add_subdirectory(Mathlib)

target_link_libraries(proj1 PUBLIC Mathlib)


