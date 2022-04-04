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
if(WIN32)
	if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
		set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/src/external/SDL2-2.0.20/lib/x64/SDL2.lib")
		set(SDL_DLL  "${CMAKE_CURRENT_LIST_DIR}/src/external/SDL2-2.0.20/lib/x64/SDL2.dll")
	else()
		set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/src/external/SDL2-2.0.20/lib/x86/SDL2.lib")
		set(SDL_DLL  "${CMAKE_CURRENT_LIST_DIR}/src/external/SDL2-2.0.20/lib/x86/SDL2.dll")
	endif()

	file(COPY ${SDL_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
elseif(UNIX)
	find_package(SDL2 REQUIRED)

	if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
		set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_LIST_DIR}/out/build/x64-Linux")
		set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
	else()
		set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_LIST_DIR}/out/build/x86-Linux")
		set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
	endif()
endif()



add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
