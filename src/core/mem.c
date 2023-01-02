#include <headers.h>

static uint8_t* mem_buffer;

//returns length of the file
static void write_rom_to_mem(const char* file_path, unsigned long rom_start){
    //creating file and checking if it is NULL
    SDL_RWops* file = NULL;

    long file_length = 0;

    file = SDL_RWFromFile(file_path, "rb");
    if (!file) { 
        log_error("%s file was null", file_path);
        deinit_manager();
    }
    else
        log_info("%s file was opened", file_path);

    //going to end of file and getting file length
    file_length = SDL_RWseek(file, 0, RW_SEEK_END);

    log_trace("FILE LENGTH %u", file_length);

    SDL_RWseek(file, 0, RW_SEEK_SET);

    for (int i = 0; i < file_length; i++)
        mem_buffer[i + rom_start] = SDL_ReadU8(file);

    //closing the file
    SDL_RWclose(file);
}

#define ROM_INVADERS_H_START 0x0000
#define ROM_INVADERS_G_START 0x0800
#define ROM_INVADERS_F_START 0x1000
#define ROM_INVADERS_E_START 0x1800

#define ROM_INVADERS_H_END 0x7FFF
#define ROM_INVADERS_G_END 0x0FFF
#define ROM_INVADERS_F_END 0x17FF
#define ROM_INVADERS_E_END 0x1FFF

/*
layout of roms in memory, param is folder path to the roms
invaders.h 0x0000-0x07FF
invaders.g 0x0800-0x0FFF
invaders.f 0x1000-0x17FF
invaders.e 0x1800-0x1FFF
*/
static void load_rom(const char* folder_path){
    write_rom_to_mem(ROM_INVADERS_H, ROM_INVADERS_H_START);
    write_rom_to_mem(ROM_INVADERS_G, ROM_INVADERS_G_START);
    write_rom_to_mem(ROM_INVADERS_F, ROM_INVADERS_F_START);
    write_rom_to_mem(ROM_INVADERS_E, ROM_INVADERS_E_START);

    //printing bytes 0x00 through 0xFF
    print_mem(0x00, 0xFF);
} 

#define MAX_FILE_LENGTH 100
#define ROM_TEST_START 0x100

static void load_tests(const char* folder_path, const char* filename) {
    char full_file_path[MAX_FILE_LENGTH];
    full_file_path[0] = '\n';

    strcpy(full_file_path, folder_path);
    strcat(full_file_path, filename);

    write_rom_to_mem(full_file_path, ROM_TEST_START);
}

void init_mem(bool load_test, const char* file_name){
    mem_buffer = (int8_t*)malloc(MEM_BUFFER_SIZE);

    if (mem_buffer)
        memset(mem_buffer, 0, MEM_BUFFER_SIZE);

    //calling test for memory
    test_read_write_mem();

    //resetting memory and loading the rom into memory
    if(mem_buffer)
        memset(mem_buffer, 0, MEM_BUFFER_SIZE);

    if (!load_test) {
        load_rom(ROM_FOLDER);
    } //NOTE load tests
    else {
        load_tests(TEST_ROM_FOLDER, file_name);
    }
}

void deinit_mem(){
    log_info("deinitializing the mem");
    free(mem_buffer);
}

uint8_t read_byte_mem(unsigned int address){
    return mem_buffer[address];
}

void write_byte_mem(unsigned int address, uint8_t value){
    mem_buffer[address] = value;
}

uint16_t read_short_mem(unsigned int address){
    return mem_buffer[address + 1] << 8 | mem_buffer[address];
}

void write_short_mem(unsigned int address, uint16_t value){
    mem_buffer[address + 1] = (value & 0xFF00) >> 8;
    mem_buffer[address] = value & 0x00FF;
}

#define COLUMNS 0x8

void print_mem(unsigned long start_address, unsigned long end_address) {
    log_info("printing mem buffer 0x%x-0x%x", start_address, end_address);
    for (int i = start_address; i <= end_address; i++) {
        log_log_nonewl("0x%02X ", (mem_buffer[i] | 0x00));

        if (((i + 1) % 8) == 0)
            log_log("");
    }
}

uint8_t* get_mem() {
    return mem_buffer;
}