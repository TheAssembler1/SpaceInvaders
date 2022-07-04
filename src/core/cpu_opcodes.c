#include <headers.h>

void nop(registers* registers, cpu_state* cpu_state){
    registers->pc++; 
    cpu_state->cycles += 4;
}

void lxi(registers* registers, cpu_state* cpu_state, int pair_register){
    load_pair_register(pair_register, read_short_mem(registers->pc + 1));

    registers->pc += 3; 
    cpu_state->cycles += 10;
}

void stax(registers* registers, cpu_state* cpu_state, int pair_register){
    write_byte_mem(read_pair_register(pair_register), registers->a);

    registers->pc++;
    cpu_state->cycles += 7;
}

void shld(registers* registers, cpu_state* cpu_state){
    write_short_mem(read_short_mem(registers->pc + 1), registers->hl);

    registers->pc += 3;
    cpu_state->cycles += 16;
}

void sta(registers* registers, cpu_state* cpu_state){
    write_byte_mem(read_short_mem(registers->pc + 1), registers->a);

    registers->pc += 3;
    cpu_state->cycles += 13;
}

void inx(registers* registers, cpu_state* cpu_state, int pair_register){
    load_pair_register(pair_register, read_pair_register(pair_register) + 1);

    registers->pc++;
    cpu_state->cycles += 5;
}

void mvi(registers* registers, cpu_state* cpu_state, int _register) {
    if (_register != M)
        load_register(_register, read_byte_mem(registers->pc + 1));
    else {
        write_byte_mem(registers->hl, read_byte_mem(registers->pc + 1));
        cpu_state->cycles += 3;
    }

    registers->pc += 2;
    cpu_state->cycles += 7;
}