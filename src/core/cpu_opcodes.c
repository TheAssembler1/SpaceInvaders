#include <headers.h>

/* Intel 8080 Manual
Description: No operation occurs. Execution proceeds
with the next sequential instruction.
*/
//NOP | 1 | 4 | - - - - -
void nop(struct registers* registers, struct cpu_state* cpu_state){
    registers->pc++;
    cpu_state->cycles += 4;
}