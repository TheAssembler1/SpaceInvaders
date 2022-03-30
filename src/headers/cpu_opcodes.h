#ifndef CPU_OPCODES_H
#define CPU_OPCODES_H

/* Intel 8080 Manual
Description: No operation occurs. Execution proceeds
with the next sequential instruction.
*/
//NOP | 1 | 4 | - - - - -
void nop(struct registers* registers, struct cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The third byte of the instruction (the
most significant 8 bits of the 16-bit immediate data) is
loaded into the first register of the specified pair, while the 
second byte of the instruction (the least significant 8 bits of
the 16-bit immediate data) is loaded into the second register
of the specified pair. If SP is specified as the register pair, the 
second byte of the instruction replaces the least significant 
8 bits of the stack pointer, while the third byte of the in-
struction replaces the most significant 8 bits of the stack 
pointer.
*/
//LXI | 3 | 10 | - - - - -
void lxi(struct registers* registers, struct cpu_state* cpu_state, int pair_register);

#endif //CPU_OPCODES_H
