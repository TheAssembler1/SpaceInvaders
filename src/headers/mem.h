#ifndef MEM_H
#define MEM_H

#define MEM_BUFFER_SIZE 0xFFFF + 1

void init_mem();
void deinit_mem();

uint8_t read_byte_mem(unsigned int address);
void write_byte_mem(unsigned int address, uint8_t value);

uint16_t read_short_mem(unsigned int address);
void write_short_mem(unsigned int address, uint16_t value);

#endif //MEM_H
