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
    load_register(_register, read_byte_mem(registers->pc + 1));

    registers->pc += 2;
    cpu_state->cycles += 7;
}

void mvi_m(registers* registers, cpu_state* cpu_state) {
    write_byte_mem(registers->hl, read_byte_mem(registers->pc + 1));

    registers->pc += 2;
    cpu_state->cycles += 10;
}

void jmp(registers* registers, cpu_state* cpu_state, uint8_t flag_distance, bool truthness, bool always_jump) {
    bool jumped = false;

    /* 
        How to check the given flag is shown by the truthness
        truthness == true -> jmp if condition is true
        truthness == false -> jmp if condition is false
    */
    if (always_jump || (truthness && BIT_TEST(registers->f, flag_distance)) || (!truthness && !BIT_TEST(registers->f, flag_distance))) {
        registers->pc = read_short_mem(registers->pc + 1);
        jumped = true;
    }
   

    if (!jumped)
        registers->pc += 3;
    cpu_state->cycles += 10;
}

void call(registers* registers, cpu_state* cpu_state, uint8_t flag_distance, bool truthness, bool always_call) {
    bool called = false;

    /*
        How to check the given flag is shown by the truthness
        truthness == true -> jmp if condition is true
        truthness == false -> jmp if condition is false
    */
    if (always_call || (truthness && BIT_TEST(registers->f, flag_distance)) || (!truthness && !BIT_TEST(registers->f, flag_distance))) {
        //NOTE: dec sp by two and store next instruction at sp
        registers->sp -= 2;
        write_short_mem(registers->sp, registers->pc + 3);

        registers->pc = read_short_mem(registers->pc + 1);
        called = true;
    }

    if (called)
        cpu_state->cycles += 17;
    else { //NOTE: call condition was not met so we just go to the next instruction
        registers->pc += 3;
        cpu_state->cycles += 10;
    }
}

void ldax(registers* registers, cpu_state* cpu_state, int _register) {
    registers->a = read_byte_mem(read_pair_register(_register));

    registers->pc++;
    cpu_state->cycles += 7;
}

void lhld(registers* registers, cpu_state* cpu_state) {
    registers->hl = read_short_mem(read_short_mem(registers->pc + 1));

    registers->pc += 3;
    cpu_state->cycles += 16;
}

void lda(registers* registers, cpu_state* cpu_state) {
    registers->a = read_byte_mem(read_short_mem(registers->pc + 1));

    registers->pc += 3;
    cpu_state->cycles += 13;
}

void mov(registers* registers, cpu_state* cpu_state, int register_dst, int register_src) {
    load_register(register_dst, read_register(register_src));

    registers->pc++;
    cpu_state->cycles += 5;
}

void mov_m(registers* registers, cpu_state* cpu_state, int _register, bool into_m) {
    //NOTE: into_m determines whether we are storing in m or getting value from m
    if (into_m)
        write_byte_mem(registers->hl, read_register(_register));
    else
        load_register(_register, read_byte_mem(registers->hl));

    registers->pc++;
    cpu_state->cycles += 7;
}

void dcr(registers* registers, cpu_state* cpu_state, int _register) {
    uint8_t intial = read_register(_register);
    uint16_t result = (uint16_t)intial - 1;

    load_register(_register, result);
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY, intial, result);

    registers->pc++;
    cpu_state->cycles += 5;
}

void dcr_m(registers* registers, cpu_state* cpu_state) {
    uint8_t intial = read_byte_mem(registers->hl);
    uint16_t result = (uint16_t)intial - 1;

    write_byte_mem(registers->hl, result);
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY, intial, result);

    registers->pc++;
    cpu_state->cycles += 10;
}

void ret(registers* registers, cpu_state* cpu_state, uint8_t flag_distance, bool truthness, bool always_return) {
    bool returned = false;

    if (always_return || (truthness && BIT_TEST(registers->f, flag_distance)) || (!truthness && !BIT_TEST(registers->f, flag_distance))) {
        registers->pc = read_short_mem(registers->sp);
        registers->sp += 2;
        returned = true;
    }

    if (!returned) {
        registers->pc++;
        cpu_state->cycles += 5;
    }
    else {
        if (always_return)
            cpu_state->cycles += 10;
        else
            cpu_state->cycles += 11;
    }
}

void dad(registers* registers, cpu_state* cpu_state, int pair_register) {
    uint16_t initial = registers->hl;
    uint32_t result = (uint32_t)registers->hl + read_pair_register(pair_register);

    registers->hl = result;
    check_set_flags(registers, CARRY, initial >> 8, result >> 8);

    registers->pc++;
    cpu_state->cycles += 10;
}

void xra(registers* registers, cpu_state* cpu_state, int _register) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial ^ read_register(_register);

    registers->a = result;
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc++;
    cpu_state->cycles += 4;
}

void xra_m(registers* registers, cpu_state* cpu_state) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial ^ read_byte_mem(registers->hl);

    registers->a = result;
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc++;
    cpu_state->cycles += 7;
}

void out(registers* registers, cpu_state* cpu_state) {
    uint8_t value = registers->a;
    uint8_t device = read_byte_mem(registers->pc + 1);

    log_info("Value 0x%02X sent to device 0x%02X", value, device);

    registers->pc += 2;
    cpu_state->cycles += 10;
}

void and(registers* registers, cpu_state* cpu_state, int _register) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial & read_register(_register);

    registers->a = result;
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc++;
    cpu_state->cycles += 4;
}

void and_m(registers* registers, cpu_state* cpu_state) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial & read_byte_mem(registers->hl);

    registers->a = result;
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc++;
    cpu_state->cycles += 7;
}