#include <headers.h>

void nop(struct registers* registers, struct cpu_state* cpu_state){
    registers->pc++; 
    cpu_state->cycles += 4;
}

void lxi(struct registers* registers, struct cpu_state* cpu_state, int pair_register){
    load_pair_register(pair_register, read_short_mem(registers->pc + 1));

    registers->pc += 3; 
    cpu_state->cycles += 10;
}

void stax(struct registers* registers, struct cpu_state* cpu_state, int pair_register){
    write_byte_mem(read_pair_register(pair_register), registers->a);

    registers->pc++;
    cpu_state->cycles += 7;
}

void shld(struct registers* registers, struct cpu_state* cpu_state){
    write_short_mem(read_short_mem(registers->pc + 1), registers->hl);

    registers->pc += 3;
    cpu_state->cycles += 16;
}

void sta(struct registers* registers, struct cpu_state* cpu_state){
    write_byte_mem(read_short_mem(registers->pc + 1), registers->a);

    registers->pc += 3;
    cpu_state->cycles += 13;
}

void inx(struct registers* registers, struct cpu_state* cpu_state, int pair_register){
    load_pair_register(pair_register, read_pair_register(pair_register) + 1);

    registers->pc++;
    cpu_state->cycles += 5;
}