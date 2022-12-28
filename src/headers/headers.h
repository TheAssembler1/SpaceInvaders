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
#define FONT_PATH "../../../res/fonts/FreeSans.ttf"
#elif defined(WINDOWS)
#define ROM_FOLDER "..\\..\\..\\rom\\"
#define FONT_PATH "..\\..\\..\\res\\fonts\\FreeSans.ttf"
#endif

#define ROM_INVADERS_E ROM_FOLDER "invaders.e"
#define ROM_INVADERS_F ROM_FOLDER "invaders.f"
#define ROM_INVADERS_G ROM_FOLDER "invaders.g"
#define ROM_INVADERS_H ROM_FOLDER "invaders.h"

//external headers
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_ttf.h>

//this projects headers
#include "log.h"
#include "cpu.h"
#include "cpu_opcodes.h"
#include "mem.h"
#include "manager.h"
#include "tests.h"
#include "gpu.h"

#endif //HEADERS_H