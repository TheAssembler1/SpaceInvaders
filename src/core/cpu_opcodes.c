#include <cpu_opcodes.h>

/* Intel 8080 Manual
Description: No operation occurs. Execution proceeds
with the next sequential instruction.
*/
//NOP | 1 | 4 | - - - - -
void nop(int selector){
    regs.pc++;
    cpu.cycles += 4;
}

/* Intel 8080 Manual
Description: The specified register or memory byte is
incremented by one
*/
//INR | 1 | 5 | S Z A P -
void inr(int selector){

}