#ifndef MEM_H
#define MEM_H

#define MEM_BUFFER_SIZE 0xFFFF + 1

void init_mem(bool load_test, char* filepath);
void deinit_mem();

uint8_t read_byte_mem(unsigned int address);
void write_byte_mem(unsigned int address, uint8_t value);

uint16_t read_short_mem(unsigned int address);
void write_short_mem(unsigned int address, uint16_t value);

void print_mem(unsigned long start_address, unsigned long end_address);

#endif //MEM_H
