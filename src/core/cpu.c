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

void log_cpu(){
    log_info("af:%hu | bc:%hu | de:%hu | hl:%hu | sp:%hu | pc:%hu",
              registers->af, registers->bc, registers->de, 
              registers->hl, registers->sp, registers->pc);
}

static void execute_opcode(uint16_t opcode){
    log_cpu();

    switch(opcode){
        case 0x00: nop(registers, cpu_state); break;
        case 0x08: nop(registers, cpu_state); break;
        case 0x10: nop(registers, cpu_state); break;
        case 0x18: nop(registers, cpu_state); break;
        case 0x20: nop(registers, cpu_state); break;
        case 0x28: nop(registers, cpu_state); break;
        case 0x30: nop(registers, cpu_state); break;
        case 0x38: nop(registers, cpu_state); break;
        default: log_error("opcode %x does not exist", opcode); deinit_manager(); break;
    }
}

void cycle_cpu(){
    while(1)
        execute_opcode(read_byte_mem(registers->pc));
}