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
typedef FILE FILE_HANDLE;
#elif defined(_WIN32) || defined(WIN32)
#define WINDOWS
#include <Windows.h>
typedef HANDLE FILE_HANDLE;
#endif

#define ROM_FOLDER "rom/"
#define ROM_INVADERS_E ROM_FOLDER "invaders.e"
#define ROM_INVADERS_F ROM_FOLDER "invaders.f"
#define ROM_INVADERS_G ROM_FOLDER "invaders.g"
#define ROM_INVADERS_H ROM_FOLDER "invaders.h"

//this projects headers
#include <log.h>
#include <cpu.h>
#include <cpu_opcodes.h>
#include <mem.h>
#include <manager.h>
#include <tests.h>
#include <file.h>

#endif //HEADERS_H