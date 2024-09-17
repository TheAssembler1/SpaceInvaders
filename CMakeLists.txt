# setting minimum cmake
cmake_minimum_required(VERSION 3.16.3)  

# headers
include_directories(src/headers/
					dep/SDL2-2.0.20/include/
					dep/SDL2_ttf-2.20.1/include/)

# here we specify that the project is C language only, so the default
# C compiler on the system will be used
project(SpaceInvaders C)

# recursively grab c files 
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")

# getting cpu arch
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
	set(CPU_ARCH "x64")
else()
	set(CPU_ARCH "x86")
endif()

# setting sdl 32 bit libraries
if(WIN32)
	# https://github.com/libsdl-org/SDL/releases/tag/release-2.0.20
	set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/dep/SDL2-2.0.20/lib/${CPU_ARCH}/SDL2.lib")
	set(SDL_DLL  "${CMAKE_CURRENT_LIST_DIR}/dep/SDL2-2.0.20/lib/${CPU_ARCH}/SDL2.dll")
	# https://www.libsdl.org/projects/SDL_ttf/release/
	set(SDL2_TTF_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/dep/SDL2_ttf-2.20.1/lib/${CPU_ARCH}/SDL2_ttf.lib")
	set(SDL_TTF_DLL  "${CMAKE_CURRENT_LIST_DIR}/dep/SDL2_ttf-2.20.1/lib/${CPU_ARCH}/SDL2_ttf.dll")

	file(COPY ${SDL_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	file(COPY ${SDL_TTF_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
elseif(UNIX)
	list(APPEND CMAKE_MODULE_PATH dep/find_cmake) 

	find_package(SDL2 REQUIRED)
        #find_package(SDL2_ttf REQUIRED)

	set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_LIST_DIR}/out/build/${CPU_ARCH}")
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
endif()



add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})
