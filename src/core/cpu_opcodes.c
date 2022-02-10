#include <cpu_opcodes.h>

//NOP | 1 | 4 | - - - - -
void nop(struct registers* reg, struct cpu_state* cpu){
    cpu->cycles += 4;
    reg->pc++;
}
