#ifndef HEADERS_H
#define HEADERS_H

//c standard headers
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

//global defines
#ifdef __unix__
#define UNIX
#elif defined(_WIN32) || defined(WIN32)
#define WINDOWS
#endif

#ifdef UNIX
#define ROM_FOLDER "../../../rom/"
#elif defined(WINDOWS)
#define ROM_FOLDER "..\\..\\..\\rom\\"
#endif

#define ROM_INVADERS_E ROM_FOLDER "invaders.e"
#define ROM_INVADERS_F ROM_FOLDER "invaders.f"
#define ROM_INVADERS_G ROM_FOLDER "invaders.g"
#define ROM_INVADERS_H ROM_FOLDER "invaders.h"

//external headers
#define SDL_MAIN_HANDLED
#include "../external/SDL2-2.0.20/include/SDL.h"

//this projects headers
#include "log.h"
#include "cpu.h"
#include "cpu_opcodes.h"
#include "mem.h"
#include "manager.h"
#include "tests.h"

#endif //HEADERS_H