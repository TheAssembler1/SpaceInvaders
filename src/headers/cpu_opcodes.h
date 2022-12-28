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

/* Intel 8080 Manual
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

/* Intel 8080 Manual
Description: The byte of immediate data is stored in
specified register or memory byte.
*/
//MVI | 2 | 7 | - - - - -
void mvi(registers* registers, cpu_state* cpu_state, int _register);
//MVI_M | 2 | 10 | - - - - -
void mvi_m(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
NOTE: This is not the description for each
jump command instead this is the general description
for all of them.

This section descrives instructions which alter the 
normal execution sequence of instructions. Note that,
just as addresses are normally stored in memory with 
the low-order byte first, so are the addresses represented
in the Jump instructions. The three-byte instructions in 
this class cause a transfer of program control depending 
upon certain specified conditions. If the specified 
condition is true, program execution will continue at the 
memory addresss formed by concantenating the 8 bits of HI 
ADD (the third byte of the instruction) with the 8 bits of 
LOW ADD (the second byte of the instruction). If the specified
condition is false, program execution will continue with the
next sequential instruction.
*/
void jmp(registers* registers, cpu_state* cpu_state, uint8_t flag_distance, bool truthness, bool always_jump);

/* Intel 8080 Manual
Note: This is not the description for each
call command instead this is the general description
for all of them.

This sections describes the instructions which call sub-
routines. These instructions operate like the jump instruc-
tions, causing a transfer of program control. In addition, a 
return address is pushed into the stack for use by the
RETURN instructions (see Return From Subroutine In-
structions later in this chapter). Instructions in this
class call subroutines upon certain specified conditions.
If the specified condition is true, a return address is pushed
into the stack and program execution continues at memory address
SUB, formed by concatenating the 8 bits of HI ADD and the 8
bits of LOW ADD, If the specified condition is false, program
execution continues with the next sequential instruction.
*/
void call(registers* registers, cpu_state* cpu_state, uint8_t flag_distance, bool truthness, bool always_call);

/* Intel 8080 Manual
Description: The contents of the memory location
addressed by registers B and C, or by registers D and E, re-
place the contents of the accumulator.
*/
void ldax(registers* registers, cpu_state* cpu_state, int _register);

/* Intel 8080 Manual
Description: the byte at the memory address formed
by concatenating HI ADD with LOW ADD replaces the con-
tents of the L register. The byte at the next higher memory
address replaces the contents of the H register.
*/
void lhld(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The byte at the memory address formed
by concatenating HI ADD with LOW ADD replaces the con-
tents of the accumulator.
*/
void lda(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: One byte of data is moved from the
register specified by src (the source register) to the register
specified by dst (the desintation register). The data re-
plces the contents of the destination register; the source
remains unchanged.
*/
//MOV | 1 | 5 | - - - - -
void mov(registers* registers, cpu_state* cpu_state, int register_dst, int register_src);

#endif //CPU_OPCODES_H 