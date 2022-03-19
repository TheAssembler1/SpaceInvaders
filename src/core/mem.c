#include <headers.h>

static uint8_t* mem_buffer;

void init_mem(){
    log_info("initializing the mem");

    mem_buffer = (int8_t*)malloc(MEM_BUFFER_SIZE);
    memset(mem_buffer, 0, MEM_BUFFER_SIZE);
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
    return mem_buffer[address + 1] << 8 & mem_buffer[address];
}

void write_short_mem(unsigned int address, uint16_t value){
    mem_buffer[address] = (value & 0xFF00) >> 8;
    mem_buffer[address] = value & 0x00FF;
}