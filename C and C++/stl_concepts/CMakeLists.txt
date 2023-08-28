
cmake_minimum_required(VERSION 3.12)
project(MyProject)

set(SOURCES MyVector.cpp main.cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define an executable target
add_executable(my_executable main.cpp)

# Include the current directory for header files
target_include_directories(my_executable PUBLIC 
                        ${CMAKE_CURRENT_SOURCE_DIR})


# configuring the valgrind target
# find_program(VALGRIND "valgrind")

# if(VALGRIND)
#    add_custom_target(valgrind
#        )

