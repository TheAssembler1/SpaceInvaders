# setting minimum cmake
cmake_minimum_required(VERSION 3.22)  

# adding the headers to the project
include_directories(src/headers/)

# here we specify that the project is C language only, so the default
# C compiler on the system will be used
project(SpaceInvaders C)

# recursively grab c files 
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")

add_executable(SpaceInvaders ${SOURCES})
