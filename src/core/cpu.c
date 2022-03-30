#include <headers.h>

static struct registers* registers;
static struct cpu_state* cpu_state;

void init_cpu(){
    log_info("initializing the cpu");

    registers = (struct registers*)malloc(sizeof(struct registers));
    cpu_state = (struct cpu_state*)malloc(sizeof(struct cpu_state));

    memset(registers, 0, sizeof(struct registers));
    memset(cpu_state, 0, sizeof(struct cpu_state));

    if(registers && cpu_state)
        log_info("success setting up cpu");
}

void deinit_cpu(){
    log_info("deinitializing the cpu");

    free(registers);
    free(cpu_state);
}

static void execute_opcode(uint16_t opcode){
    switch(opcode){
        case 0x00: nop(registers, cpu_state); break;
        case 0x01: lxi(registers, cpu_state, BC); break;
        case 0x08: nop(registers, cpu_state); break;
        case 0x10: nop(registers, cpu_state); break;
        case 0x11: lxi(registers, cpu_state, DE); break;
        case 0x18: nop(registers, cpu_state); break;
        case 0x20: nop(registers, cpu_state); break;
        case 0x21: lxi(registers, cpu_state, HL); break;
        case 0x28: nop(registers, cpu_state); break;
        case 0x30: nop(registers, cpu_state); break;
        case 0x31: lxi(registers, cpu_state, SP); break;
        case 0x38: nop(registers, cpu_state); break;
        default: log_error("opcode %x does not exist", opcode); deinit_manager(); break;
    }
}

void cycle_cpu(){
    while(1)
        execute_opcode(read_byte_mem(registers->pc));
}

void load_register(int _register, uint8_t value){
    switch(_register){
        case A: registers->a = value; break; case F: registers->f = value; break;
        case B: registers->b = value; break; case C: registers->c = value; break;
        case D: registers->d = value; break; case E: registers->e = value; break;
        case H: registers->h = value; break; case L: registers->l = value; break;
        default: log_error("register %u does not exist", value); deinit_manager(); break;
    }
}

void load_pair_register(int pair_register, uint16_t value){
    switch(pair_register){
        case AF: registers->af = value; break;
        case BC: registers->bc = value; break;
        case DE: registers->de = value; break;
        case HL: registers->hl = value; break;
        case SP: registers->sp = value; break;
        default: log_error("pair register %u does not exist", value); deinit_manager(); break;
    }
}