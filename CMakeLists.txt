# setting minimum cmake
cmake_minimum_required(VERSION 3.16.3)  

# adding the headers to the project
include_directories(src/headers/)

# here we specify that the project is C language only, so the default
# C compiler on the system will be used
project(SpaceInvaders C)

# recursively grab c files 
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")

#setting sdl 32 bit libraries
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
	set(SDL2_LIB "${CMAKE_CURRENT_LIST_DIR}/src/external/SDL2-2.0.20/lib/x64/SDL2.lib")
	set(SDL_DLL  "${CMAKE_CURRENT_LIST_DIR}/src/external/SDL2-2.0.20/lib/x64/SDL2.dll")

	#setting output directory of were are on linux
	if(UNIX)
		set(CMAKE_CURRENT_BINARY_DIR, "${CMAKE_CURRENT_LIST_DIR}/out/build/x64-Linux/")
	endif()
else()
	set(SDL2_LIB "${CMAKE_CURRENT_LIST_DIR}/src/external/SDL2-2.0.20/lib/x86/SDL2.lib")
	set(SDL_DLL  "${CMAKE_CURRENT_LIST_DIR}/src/external/SDL2-2.0.20/lib/x86/SDL2.dll")

	#setting output directory of were are on linux
	if(UNIX)
		set(CMAKE_CURRENT_BINARY_DIR, "${CMAKE_CURRENT_LIST_DIR}/out/build/x86-Linux/")
	endif()
endif()

file(COPY ${SDL_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIB})
