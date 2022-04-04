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
    SDL_RWseek(file, 0, RW_SEEK_END);   
    file_length = SDL_RWtell(file);
    SDL_RWseek(file, 0, RW_SEEK_SET);

    for (int i = 0; i <= file_length; i++) {
        mem_buffer[i + rom_start] = SDL_ReadU8(file);
        SDL_RWseek(file, 1, RW_SEEK_CUR);
    }

    //closing the file
    SDL_RWclose(file);

    /*
    FILE* file = NULL;
    long file_length = 0;
    file = fopen(file_path, "rb");

    (!file) ? log_error("%s file was null", file_path) : log_info("%s file was opened", file_path);

    //getting the length of the file
    fseek(file, 0, SEEK_END);
    file_length = ftell(file);
    rewind(file);

    if(fread(&mem_buffer[rom_start], 1, file_length, file) == file_length)
        log_info("%s was successfully written to mem_buffer", file_path);
    else
        log_error("%s was unsuccessfully written to mem_buffer", file_path);

    fclose(file);
    */
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
}   

void init_mem(){
    mem_buffer = (int8_t*)malloc(MEM_BUFFER_SIZE);

    //calling test for memory
    test_read_write_mem();

    //resetting memory and loading the rom into memory
    if(mem_buffer)
        memset(mem_buffer, 0, MEM_BUFFER_SIZE);

    load_rom(ROM_FOLDER);
}

void deinit_mem(){
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