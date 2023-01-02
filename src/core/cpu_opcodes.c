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

void jmp(registers* registers, cpu_state* cpu_state, bool should_jmp) {
    /* 
        How to check the given flag is shown by the truthness
        truthness == true -> jmp if condition is true
        truthness == false -> jmp if condition is false
    */
    if(should_jmp){
        registers->pc = read_short_mem(registers->pc + 1);
    }
    else {
        registers->pc += 3;
    }

    cpu_state->cycles += 10;
}

void call(registers* registers, cpu_state* cpu_state, bool should_call) {
    if (should_call) {
        //NOTE: dec sp by two and store next instruction at sp
        registers->sp -= 2;
        write_short_mem(registers->sp, registers->pc + 3);

        registers->pc = read_short_mem(registers->pc + 1);
        cpu_state->cycles += 17;
    }
    else {
        registers->pc += 3;
        cpu_state->cycles += 10;
    }
}

void ldax(registers* registers, cpu_state* cpu_state, int pair_register) {
    registers->a = read_byte_mem(read_pair_register(pair_register));

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
    if (into_m) {
        write_byte_mem(registers->hl, read_register(_register));
    }
    else {
        load_register(_register, read_byte_mem(registers->hl));
    }

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

void ret(registers* registers, cpu_state* cpu_state, bool should_ret) {
    if(should_ret){
        registers->pc = read_short_mem(registers->sp);
        registers->sp += 2;

        cpu_state->cycles += 10;
    }
    else {
        registers->pc++;
        cpu_state->cycles += 5;
    }
}

void dad(registers* registers, cpu_state* cpu_state, int pair_register) {
    uint16_t initial = registers->hl;
    uint32_t result = (uint32_t)initial + read_pair_register(pair_register);

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

#define SHIFT_OUT 0x04
#define SHIFT_OUT_OFFSET 0x02

uint8_t offset = 0;

typedef union{
    struct {
        uint8_t low_value;
        uint8_t high_value;
    };
    uint16_t value;
} _shift_register;

_shift_register shift_register;

#define SHIFT_AND_BITS 0b00000111

void out(registers* registers, cpu_state* cpu_state) {
    uint8_t value = registers->a;
    uint8_t device = read_byte_mem(registers->pc + 1);

    if (device == SHIFT_OUT) {
        shift_register.low_value = shift_register.high_value;
        shift_register.high_value = value;
    }
    else if (device == SHIFT_OUT_OFFSET) {
        offset = value & SHIFT_AND_BITS;
    }

    //log_info("Value 0x%02X sent to device 0x%02X", value, device);

    registers->pc += 2;
    cpu_state->cycles += 10;
}

void ana(registers* registers, cpu_state* cpu_state, int _register) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial & read_register(_register);

    registers->a = result;
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc++;
    cpu_state->cycles += 4;
}

void ana_m(registers* registers, cpu_state* cpu_state) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial & read_byte_mem(registers->hl);

    registers->a = result;
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc++;
    cpu_state->cycles += 7;
}

void push(registers* registers, cpu_state* cpu_state, int pair_register) {
    registers->sp -= 2;
    write_short_mem(registers->sp, read_pair_register(pair_register));

    registers->pc++;
    cpu_state->cycles += 11;
}

void pop(registers* registers, cpu_state* cpu_state, int pair_register) {
    load_pair_register(pair_register, read_short_mem(registers->sp));
    registers->sp += 2;

    registers->pc++;
    cpu_state->cycles += 10;
}

void xchg(registers* registers, cpu_state* cpu_state) {
    uint16_t temp = registers->hl;
    registers->hl = registers->de;
    registers->de = temp;

    registers->pc++;
    cpu_state->cycles += 5;
}

void rlc(registers* registers, cpu_state* cpu_state) {
    registers->f = (BIT_TEST(registers->a, 7)) ? BIT_SET(registers->f, CARRY_DISTANCE) : BIT_CLEAR(registers->f, CARRY_DISTANCE);
    registers->a = rotl(registers->a);

    registers->pc++;
    cpu_state->cycles += 4;
}

void rrc(registers* registers, cpu_state* cpu_state) {
    registers->f = (BIT_TEST(registers->a, 0)) ? BIT_SET(registers->f, CARRY_DISTANCE) : BIT_CLEAR(registers->f, CARRY_DISTANCE);
    registers->a = rotr(registers->a);

    registers->pc++;
    cpu_state->cycles += 4;
}

void ral(registers* registers, cpu_state* cpu_state) {
    uint8_t prev_a = registers->a;

    registers->a <<= 1;

    registers->a = (BIT_TEST(registers->f, CARRY_DISTANCE)) ? BIT_SET(registers->a, 0) : BIT_CLEAR(registers->a, 0);
    registers->f = (BIT_TEST(prev_a, 7)) ? BIT_SET(registers->f, CARRY_DISTANCE) : BIT_CLEAR(registers->f, CARRY_DISTANCE);

    registers->pc++;
    cpu_state->cycles += 4;
}

void rar(registers* registers, cpu_state* cpu_state) {
    uint8_t prev_a = registers->a;

    registers->a >>= 1;

    registers->a = (BIT_TEST(registers->f, CARRY_DISTANCE)) ? BIT_SET(registers->a, 7) : BIT_CLEAR(registers->a, 7);
    registers->f = (BIT_TEST(prev_a, 0)) ? BIT_SET(registers->f, CARRY_DISTANCE) : BIT_CLEAR(registers->f, CARRY_DISTANCE);

    registers->pc++;
    cpu_state->cycles += 4;
}

void adi(registers* registers, cpu_state* cpu_state) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial + read_byte_mem(registers->pc + 1);

    registers->a = result;
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc += 2;
    cpu_state->cycles += 7;
}

void sui(registers* registers, cpu_state* cpu_state) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial - read_byte_mem(registers->pc + 1);

    registers->a = result;
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc += 2;
    cpu_state->cycles += 7;
}

void ani(registers* registers, cpu_state* cpu_state) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial & read_byte_mem(registers->pc + 1);

    registers->a = result;
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc += 2;
    cpu_state->cycles += 7;
}

void ori(registers* registers, cpu_state* cpu_state) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial | read_byte_mem(registers->pc + 1);

    registers->a = result;
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc += 2;
    cpu_state->cycles += 7;
}

void aci(registers* registers, cpu_state* cpu_state) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial + read_byte_mem(registers->pc + 1);

    result += (BIT_TEST(registers->f, CARRY_DISTANCE)) ? 1 : 0;

    registers->a = result;
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc += 2;
    cpu_state->cycles += 7;
}

void sbi(registers* registers, cpu_state* cpu_state) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial - read_byte_mem(registers->pc + 1);

    result -= (BIT_TEST(registers->f, CARRY_DISTANCE)) ? 1 : 0;

    registers->a = result;
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc += 2;
    cpu_state->cycles += 7;
}

void xri(registers* registers, cpu_state* cpu_state) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial ^ read_byte_mem(registers->pc + 1);

    registers->a = result;
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc += 2;
    cpu_state->cycles += 7;
}

void cpi(registers* registers, cpu_state* cpu_state) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial - read_byte_mem(registers->pc + 1);

    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc += 2;
    cpu_state->cycles += 7;
}

void ei(registers* registers, cpu_state* cpu_state) {
    cpu_state->interrupts_enabled = true;

    registers->pc++;
    cpu_state->cycles += 4;
}

void di(registers* registers, cpu_state* cpu_state) {
    cpu_state->interrupts_enabled = false;

    registers->pc++;
    cpu_state->cycles += 4;
}

void rst(registers* registers, cpu_state* cpu_state, uint16_t address) {
    cpu_state->interrupts_enabled = false;

    registers->sp -= 2;
    write_short_mem(registers->sp, registers->pc);

    registers->pc = address;
}

#define SHIFT_IN_DEVICE 0x03

//FIXME:: read input from device
//Current just reading a in from device;
void in(registers* registers, cpu_state* cpu_state) {
    int device = read_byte_mem(registers->pc + 1);

    if (device == SHIFT_IN_DEVICE) {
        registers->a = (((shift_register.high_value << 8) | shift_register.low_value) << offset) >> 8;
    }

    //log_info("Value 0x%02X sent from device 0x%02X", value, device);

    registers->pc += 2;
    cpu_state->cycles += 10;
}

void daa(registers* registers, cpu_state* cpu_state) {    
    if ((registers->a & 0x0F) > 0x09 || BIT_TEST(registers->f, AUX_CARRY_DISTANCE)) {
        registers->a += 0x06;
        registers->f = BIT_SET(registers->f, AUX_CARRY_DISTANCE);
    }
    else {
        registers->f = BIT_CLEAR(registers->f, AUX_CARRY_DISTANCE);
    }

    if (registers->a > 0x9F || BIT_TEST(registers->f, CARRY_DISTANCE)) {
        registers->a += 0x60;
        registers->f = BIT_SET(registers->f, CARRY_DISTANCE);
    }
    else {
        registers->f = BIT_CLEAR(registers->f, CARRY_DISTANCE);
    }

    check_set_flags(registers, ZERO | SIGN | PARRY, NULL, registers->a);

    registers->pc++;
    cpu_state->cycles += 4;
}

void stc(registers* registers, cpu_state* cpu_state) {
    registers->f = BIT_SET(registers->f, CARRY_DISTANCE);

    registers->pc++;
    cpu_state->cycles += 4;
}

void dcx(registers* registers, cpu_state* cpu_state, int pair_register) {
    load_pair_register(pair_register, read_pair_register(pair_register) - 1);

    registers->pc++;
    cpu_state->cycles += 5;
}

void ora(registers* registers, cpu_state* cpu_state, int _register) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial | read_register(_register);

    registers->a = result;
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc++;
    cpu_state->cycles += 4;
}

void ora_m(registers* registers, cpu_state* cpu_state) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial | read_byte_mem(registers->hl);

    registers->a = result;
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc++;
    cpu_state->cycles += 7;
}

void inr(registers* registers, cpu_state* cpu_state, int _register) {
    uint8_t intial = read_register(_register);
    uint16_t result = (uint16_t)intial + 1;

    load_register(_register, result);
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY, intial, result);

    registers->pc++;
    cpu_state->cycles += 5;
}

void inr_m(registers* registers, cpu_state* cpu_state) {
    uint8_t intial = read_byte_mem(registers->hl);
    uint16_t result = (uint16_t)intial + 1;

    write_byte_mem(registers->hl, result);
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY, intial, result);

    registers->pc++;
    cpu_state->cycles += 10;
}

void sphl(registers* registers, cpu_state* cpu_state) {
    registers->sp = registers->hl;

    registers->pc++;
    cpu_state->cycles += 5;
}

void xthl(registers* registers, cpu_state* cpu_state) {
    uint16_t temp = registers->hl;
    registers->hl = read_short_mem(registers->sp);
    write_short_mem(registers->sp, temp);

    registers->pc++;
    cpu_state->cycles += 18;
}

void pchl(registers* registers, cpu_state* cpu_state) {
    registers->pc = registers->hl;

    cpu_state->cycles += 5;
}

void add(registers* registers, cpu_state* cpu_state, int _register) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial + read_register(_register);

    registers->a = result;
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc++;
    cpu_state->cycles += 4;
}

void add_m(registers* registers, cpu_state* cpu_state) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial + read_byte_mem(registers->hl);

    registers->a = result;
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc++;
    cpu_state->cycles += 7;
}

void sub(registers* registers, cpu_state* cpu_state, int _register) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial - read_register(_register);

    registers->a = result;
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc++;
    cpu_state->cycles += 4;
}

void sub_m(registers* registers, cpu_state* cpu_state) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial - read_byte_mem(registers->hl);

    registers->a = result;
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc++;
    cpu_state->cycles += 7;
}

void adc(registers* registers, cpu_state* cpu_state, int _register) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial + read_register(_register);

    result += (BIT_TEST(regs->f, CARRY_DISTANCE)) ? 1 : 0;

    registers->a = result;
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc++;
    cpu_state->cycles += 4;
}

void adc_m(registers* registers, cpu_state* cpu_state) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial + read_byte_mem(registers->hl);

    result += (BIT_TEST(regs->f, CARRY_DISTANCE)) ? 1 : 0;

    registers->a = result;
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc++;
    cpu_state->cycles += 7;
}

void sbb(registers* registers, cpu_state* cpu_state, int _register) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial - read_register(_register);

    result -= (BIT_TEST(regs->f, CARRY_DISTANCE)) ? 1 : 0;

    registers->a = result;
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc++;
    cpu_state->cycles += 4;
}

void sbb_m(registers* registers, cpu_state* cpu_state) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial - read_byte_mem(registers->hl);

    result -= (BIT_TEST(regs->f, CARRY_DISTANCE)) ? 1 : 0;

    registers->a = result;
    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc++;
    cpu_state->cycles += 7;
}

void cmp(registers* registers, cpu_state* cpu_state, int _register) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial - read_register(_register);

    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc++;
    cpu_state->cycles += 4;
}

void cmp_m(registers* registers, cpu_state* cpu_state) {
    uint8_t initial = registers->a;
    uint16_t result = (uint16_t)initial - read_byte_mem(registers->hl);

    check_set_flags(registers, SIGN | ZERO | AUX_CARRY | PARRY | CARRY, initial, result);

    registers->pc++;
    cpu_state->cycles += 7;
}

void cmc(registers* registers, cpu_state* cpu_state) {
    registers->f = BIT_FLIP(registers->f, CARRY_DISTANCE);

    registers->pc++;
    cpu_state->cycles += 4;
}

void cma(registers* registers, cpu_state* cpu_state) {
    for (int i = 0; i < 8; i++)
        registers->a = BIT_FLIP(registers->a, i);

    registers->pc++;
    cpu_state->cycles += 4;
}

void hlt(registers* registers, cpu_state* cpu_state) {
    cpu_state->halted = true;

    registers->pc++;
    cpu_state->cycles += 7;
}