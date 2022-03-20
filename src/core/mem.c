#include <headers.h>

static uint8_t* mem_buffer;

//returns length of the file
static unsigned long open_file_for_reading_bytes(FILE** file, const char* file_path){
    long file_length = 0;
    *file = fopen(file_path, "rb");

    (!*file) ? log_error("%s file was null", file_path) : log_info("%s file was opened", file_path);

    //getting the length of the file
    fseek(*file, 0, SEEK_END);
    file_length = ftell(*file);
    rewind(*file);

    return file_length;
}

#define ROM_INVADERS_H_START 0x0000
#define ROM_INVADERS_G_START 0x0FFF
#define ROM_INVADERS_F_START 0x17FF
#define ROM_INVADERS_E_START 0x1FFF

/*
layout of roms in memory, param is folder path to the roms
invaders.h 0x0000-0x07FF
invaders.g 0x0800-0x0FFF
invaders.f 0x1000-0x17FF
invaders.e 0x1800-0x1FFF
*/
static void load_rom(const char* folder_path){
    FILE* file = NULL;
    long file_length = 0;

    log_info("file path to invaders.h:%s", ROM_INVADERS_H);
    log_info("file path to invaders.g:%s", ROM_INVADERS_G);
    log_info("file path to invaders.f:%s", ROM_INVADERS_F);
    log_info("file path to invaders.e:%s", ROM_INVADERS_E);

    file_length = open_file_for_reading_bytes(&file, ROM_INVADERS_H);
    if(fread(&mem_buffer[ROM_INVADERS_H_START], 1, file_length, file) == file_length)
        log_info("%s was successfully written to mem_buffer", ROM_INVADERS_H);
    else
        log_error("%s was unsuccessfully written to mem_buffer", ROM_INVADERS_H);

    file_length = open_file_for_reading_bytes(&file, ROM_INVADERS_G);
    if(fread(&mem_buffer[ROM_INVADERS_G_START], 1, file_length, file) == file_length)
        log_info("%s was successfully written to mem_buffer", ROM_INVADERS_G);
    else
        log_error("%s was unsuccessfully written to mem_buffer", ROM_INVADERS_G);

    file_length = open_file_for_reading_bytes(&file, ROM_INVADERS_F);
    if(fread(&mem_buffer[ROM_INVADERS_F_START], 1, file_length, file) == file_length)
        log_info("%s was successfully written to mem_buffer", ROM_INVADERS_F);
    else
        log_error("%s was unsuccessfully written to mem_buffer", ROM_INVADERS_F);

    file_length = open_file_for_reading_bytes(&file, ROM_INVADERS_E);
    if(fread(&mem_buffer[ROM_INVADERS_E_START], 1, file_length, file) == file_length)
        log_info("%s was successfully written to mem_buffer", ROM_INVADERS_E);
    else
        log_error("%s was unsuccessfully written to mem_buffer", ROM_INVADERS_E);

    fclose(file);
}   

void init_mem(){
    log_info("initializing the mem");

    mem_buffer = (int8_t*)malloc(MEM_BUFFER_SIZE);

    //calling test for memory
    test_read_write_mem();

    //resetting memory and loading the rom into memory
    memset(mem_buffer, 0, MEM_BUFFER_SIZE);
    load_rom(ROM_FOLDER);
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