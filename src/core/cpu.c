#include "cpu.h"

#define NUM_OPCODES 0xFF

static registers regs;

static void (*execute[NUM_OPCODES])() = {
    test
};

void init_cpu(){
}

void execute_opcode(uint16_t opcode){
   (*execute[])(); 
}
