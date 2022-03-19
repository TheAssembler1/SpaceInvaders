#include <headers.h>

static struct registers* registers;
static struct cpu_state* cpu_state;

void init_cpu(){
    log_info("initializing the cpu");

    registers = (struct registers*)malloc(sizeof(struct registers));
    cpu_state = (struct cpu_state*)malloc(sizeof(struct cpu_state));

    if(registers && cpu_state)
        log_info("success setting up cpu");
}

void log_cpu(){
    log_info("af:%u | bc:%u | de:%u | hl:%u | sp:%u | pc:%u",
              registers->af, registers->bc, registers->de, 
              registers->hl, registers->sp, registers->pc);
}

void log_flags(){

}

void execute_opcode(uint16_t opcode){
    log_cpu();

    switch(opcode){
        case 0x00: nop(registers, cpu_state); break;
    }
}