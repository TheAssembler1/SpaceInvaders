#ifndef HEADERS_H
#define HEADERS_H

//global defines
#ifdef __unix__
#define UNIX
#elif defined(_WIN32) || defined(WIN32) || defined(WIN64)
#define WINDOWS
#endif

#define ROM_FOLDER "rom/"
#define ROM_INVADERS_E ROM_FOLDER "invaders.e"
#define ROM_INVADERS_F ROM_FOLDER "invaders.f"
#define ROM_INVADERS_G ROM_FOLDER "invaders.g"
#define ROM_INVADERS_H ROM_FOLDER "invaders.h"

//c standard headers
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

//3rs party headers
#include <log.h>

//this projects headers
#include <cpu.h>
#include <cpu_opcodes.h>
#include <mem.h>
#include <manager.h>
#include <tests.h>

#endif //HEADERS_H