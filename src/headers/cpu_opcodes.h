#ifndef CPU_OPCODES_H
#define CPU_OPCODES_H

/* Intel 8080 Manual
Description: No operation occurs. Execution proceeds
with the next sequential instruction.
*/
//NOP | 1 | 4 | - - - - -
void nop();

/* Intel 8080 Manual
Description: The specified register or memory byte is
incremented by one
*/
//INR | 1 | 5 | S Z A P -
void inr();

#endif
