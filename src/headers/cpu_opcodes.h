#ifndef CPU_OPCODES_H
#define CPU_OPCODES_H

/* Intel 8080 Manual
Description: No operation occurs. Execution proceeds
with the next sequential instruction.
*/
//NOP | 1 | 4 | - - - - -
void nop(registers* registers, cpu_state* cpu_state);

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
void lxi(registers* registers, cpu_state* cpu_state, int pair_register);

/* Intel 8080 Manul
Description: The contents of the accumulator are 
stored in the memory location addressed by registers B and 
C, or by registers D and E.
*/
//STAX | 1 | 7 | - - - - -
void stax(registers* registers, cpu_state* cpu_state, int pair_register);

/* Intel 8080 Manual
Description: The contents of the L register are stored
at the memory address formed by concatenating HI ADD
with LOW ADD. The contents of the H register are stored at
the next higher memory address.
*/
//SHLD | 3 | 16 | - - - - -
void shld(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The contents of the accumulator replace
the byte at the memory address formed by concatenating
HI ADD and LOW ADD.
*/
//STA | 3 | 13 | - - - - -
void sta(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The 16-bit number held in the specified
register pair is incremented by one.
*/
//INX | 1 | 5 | - - - - -
void inx(registers* registers, cpu_state* cpu_state, int pair_register);

#endif //CPU_OPCODES_H