#include "cpu.h"

#define NUM_OPCODES 0xFF

static registers regs;
static cpu_state cpu;

static void (*execute[NUM_OPCODES])() = {
    test
};

void init_cpu(){
}

void execute_opcode(uint16_t opcode){
   (*execute[])(registers* regs, cpu_state* cpu); 
}
