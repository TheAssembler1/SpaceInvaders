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
//JMP | 3 | 10 | - - - - -
void jmp(registers* registers, cpu_state* cpu_state, bool should_jmp);

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
//CALL | 3 | 17/11 | - - - - - 
void call(registers* registers, cpu_state* cpu_state, bool should_call);

/* Intel 8080 Manual
Description: The contents of the memory location
addressed by registers B and C, or by registers D and E, re-
place the contents of the accumulator.
*/
//LDAX | 1 | 7 | - - - - -
void ldax(registers* registers, cpu_state* cpu_state, int _register);

/* Intel 8080 Manual
Description: the byte at the memory address formed
by concatenating HI ADD with LOW ADD replaces the con-
tents of the L register. The byte at the next higher memory
address replaces the contents of the H register.
*/
//LHLD | 3 | 16 | - - - - -
void lhld(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The byte at the memory address formed
by concatenating HI ADD with LOW ADD replaces the con-
tents of the accumulator.
*/
//LDA | 3 | 13 | - - - - -
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
//MOV_M | 1 | 7 | - - - - -
void mov_m(registers* registers, cpu_state* cpu_state, int _register, bool into_m);

/* Intel 8080 Manual
Description: The specified register or memory byte is
decremented by one.
*/
//DCR | 1 | 5 | S Z A P -
void dcr(registers* registers, cpu_state* cpu_state, int _register);
//DCR_M | 1 | 10 | S Z A P -
void dcr_m(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
NOTE: This is not the description for each
jump command instead this is the general description
for all of them.

This section describes the instructions used to return
from subroutines. These instructions pop the last address
saved on the stack into the program counter, cause a trans-
fer of program control to that address. 
Instructions in this class perform RETURN operations 
upon certain specified conditions. If the specified condition
is true, a return operation is performed. Otherwise, program
execution continues with the next sequential instruction.
*/
//RET | 1 | 4/10/11 | - - - - - 
void ret(registers* registers, cpu_state* cpu_state, bool should_ret);

/* Intel 8080 Manual
Description: The 16-bit number in the specified regis-
ter pair is added to the 16-bit number held in the H and L
registers using two's complement arithmetic. The result re-
places the contents of the H and L registers.
*/
//DAD | 1 | 10 | - - - - C
void dad(registers* registers, cpu_state* cpu_state, int pair_register);

/* Intel 8080 Manual
Description: The specified byte is EXCLUSIVE-ORed 
bit by bit with the contents of the accumulator. The Carry
bit is reset to zero.
*/
//XRA | 1 | 4 | S Z A P C
void xra(registers* registers, cpu_state* cpu_state, int _register);
//XRA | 1 | 7 | S Z A P C
void xra_m(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The contents of the accumulator are sent
to output device number exp.
*/
//OUT | 2 | 10 | - - - - -
void out(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The specified byte is logically ANDed bit
by bit with the contents of the accumulator. The Carry bit
is reset to zero.
*/
//ANA | 1 | 4 | S Z A P C
void ana(registers* registers, cpu_state* cpu_state, int _register);
//ANA_M | 1 | 7 | S Z A P C
void ana_m(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The contents of the specified register pair
are saved in two bytes of memory indicated by the stack
pointer SP.
The contents of the first register are saved at the mem-
ory address one les than the address indicated by the stack
pointer; the contents of the second register are saed at the
address two less than the address indicated by the stack
pointer. If register pair PSW is specified, the first byte of in-
formation saved holds the contents of the A register; the
second byte holds the settings of the five condition bits,
i.e., Carry, Zero, Parity, and Auxiliary Carry. 
In any case, after the data has been saved, the stack
pointer is decremented by two.
*/
//PUSH | 1 | 11 | - - - -
void push(registers* registers, cpu_state* cpu_state, int pair_register);

/* Intel 8080 Manual
Description: The contents of the specified register pair
are stored from two bytes of memory indicated by the
stack pointer SP. The byte of data at the memory address
indicated by the stack pointer is loaded into the second
register of the register pair, the byte of data at the address
on greater than the address indicated by the stack pointer
is loaded into the first register of the pair. If register pair
PSW is specified, the byte of data indicated by the contents
of the stack pointer plus one is used to restore the values of
the five condition bits (Carry, Zero, Sign, Parity, and Aux-
iliary Carry) using the format described in the last section.
In any case, after the data has been restored, the stack
pointer is incremented by two.
*/
//POP | 1 | 10 | - - - - -
void pop(registers* registers, cpu_state* cpu_state, int pair_register);

/* Intel 8080 Manual
Description: The 16 bits of data held in in the H and L
registers are exchanged withe 16 bits of data held in the
D and E registers.
*/
//XCHG | 1 | 5 | - - - -
void xchg(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The Carry bit is set equal to the high-
order bit of the accumulator. The contents of the accumu-
lator are rotated one bit position to the left with the high-
order bit being transferred to the low-order bit position of
the accumulator.
*/
//RLC | 1 | 4 | - - - - C
void rlc(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The carry bit is set to equal to the low-order
bit of the accumulator. The contents of the accumulator are
rotated one bit position to the right, with the low-order bit
being transferred to the high-order bit position of the 
accumulator.
*/
//RRC | 1 | 4 | - - - - C
void rrc(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The contents of the accumulator are ro-
tated one bit position to the left.
The high-order bit of the accumulator replaces the 
Carry bit, while the Carry bit replaces the high-order bit of
the accumulator.
*/
//RAL | 1 | 4 | - - - - C
void ral(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The contents of the accumulator are ro-
tated one bit position to the right.
The low-order bit of the accumulator replaces the
carry bit, while the carry bit replaces the high-order bit of
the accumulator.
*/
//RAR | 1 | 4 | - - - - C
void rar(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The byte of immediate data is added to
the contents of the accumulaotr using two's complement
arithmetic.
*/
//ADI | 2 | 7 | S Z A P C
void adi(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The byte of immediate data is subtracted
from the contents of the accumulator using two's comple-
ment arithmetic.
*/
//SUI | 2 | 7 | S Z A P C
void sui(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The byte of immediate data is logically 
ANDed with the contents of the accumulator, The Carry bit
is reset to zero
*/
//ANI | 2 | 7 | S Z A P C
void ani(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The byte of immediate data is logically 
ORed with the contents of the accumulator.
*/
//ORI | 2 | 7 | S Z A P C
void ori(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The byte of immediate data is added to
the contents of the accumulator plus the contents of the
carry bit.
*/
//ACI | 2 | 7 | S Z A P C
void aci(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: the carry bit is internally added to the
byte of immediate data. This values is then subtracted from
the accumulator using two's complement arithmetic.
this instuction and the SBB instruction are most use-
ful when performing multibyte subtractions. 
*/
//SBI | 2 | 7 | S Z A P C
void sbi(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The byte of immediate data is EXCLU-
SIVE-ORed with the contents of the accumulator. The carry
bit is set to zero.
*/
//XRI | 2 | 7 | S Z A P C 
void xri(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The byte of immediate data is compared
to the contents of the accumulator.
The comparison is performed by internally substract-
ing the data from the accumulator using two's copmlement
arithmetic, leaving the accumulator unchanged but setting
the condition bits by the result.
In particular, the zero bit is set if the qunatities are
equal, and reset if they are unequal.
Since a substract operation is performed, the Carry bit
will be set if there is no carry out of bit 7, indicating the
immediate data is greater than the contents of the accumu-
lator, and reset otherwise.
*/
//CPI | 2 | 7 | S Z A P C
void cpi(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: This instruction sets the INTE flip-flop,
enabling the cpu to recognize and respond to interrupts.
*/
//EI | 1 | 4 | - - - -
void ei(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: This instruction resets the INTE flip-flop
causing the CPU to ignore all interrupts.
*/
//DI | 1 | 4 | - - - -
void di(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The contents of the program counter
are pushed onto the stack, providing a return address for
later use by a RETURN instruction. 
Program execution continues at memory address:
	0000000000EXP000B
Normally, this instruction is used in conjunction with
up to eight eight-byte routines in the lower 64 word of
memory in order to service interrupts to the processor. The
intterrupting device causes a particular RST instruction to be
executed, transferring control to a subroutine which deals 
with the situation as described in Section 6.
A RETURN instruction then causes the program 
which was originally running to resume execution at the
instruction where the interrupt occured.

NOTE: Byte Examples
0b0000000000 000 000
0b0000000000 001 000
0b0000000000 010 000
0b0000000000 011 000
0b0000000000 100 000
0b0000000000 101 000
0b0000000000 110 000
0b0000000000 111 000
*/
//RST | 1 | 11 | - - - - -
void rst(registers* registers, cpu_state* cpu_state, uint16_t address);

/* Intel 8080 Manual
Description: An eight-bit data byte is read from input
device number exp and replaces the contents of the 
accumulator.
*/
//IN | 2 | 10 | - - - - -
void in(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The eight-bit hexadecimal number in the
accumulator is adjusted to form two four-bit binary-coded
decimal digits by the following two step process
1. If the least significant bits of the accumualtor
represents a number greater than 9, or if the Auxiliary
Carry bit is equal t oone, the accumulator is incre-
mented by six. Otherwise, no incrementing occurs.
2. If the most significant four bits of the accumulator
now represent a number greater than 9, or if the nor-
mal carry bit is equal to one, the most significant four
bits of the accumulator are incremented by six. Other-
wise, no incrementing occurs.
If a carry out of the least significatn four bits occurs 
during Step(1), the Auxiliary Carry Bit is set; otherwise it is
reset. Likewise, if a carry out bit of the most significant four
bigs occurs during Step(2), the normal Carry bit is set;
otherwise, it is unaffected.
*/
//DAA | 1 | 4 | S Z A P C
void daa(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The Carry bit is set to one.
*/
//STC | 1 | 4 | - - - - C
void stc(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The 16-bit number held in the specified
register pair is decremented by one.
*/
//dcx | 1 | 5 | - - - - -
void dcx(registers* registers, cpu_state* cpu_state, int pair_register);

/* Intel 8080 Manua
Description: The specified byte is logically ORed bit
by bit with the contents of the accumulator. The carry bit
is reset to zero.
*/
//ORA | 1 | 4 | S Z A P C
void ora(registers* registers, cpu_state* cpu_state, int _register);
//ORA_M | 1 | 4 | S Z A P C
void ora_m(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The specified register or memory byte is
incremented by one.
*/
//INR | 1 | 5 | S Z A P -
void inr(registers* registers, cpu_state* cpu_state, int _register);
//INR_M | 1 | 10 | S Z A P -
void inr_m(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The 16 bits of data held in the H and L
registers replace the contents of the stack pointer SP. The
contents of the H and L registers are unchanged
*/
//SPHL | 1 | 5 | - - - - -
void sphl(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The contents of the L register are ex-
changed with the contents of the memory byte whose ad-
dress is held in the stack pointer SP. The contents of the H
register are exchanged with the contents of the memory
byte whose address is one greater than that held in the stack 
pointer.
*/
//XTHL | 1 | 18 | - - - - -
void xthl(registers* registers, cpu_state* cpu_state);


/* Intel 8080 Manual
Description: The 16 bits of data held in pc
register replaces the contents of the stack pointer SP. The
contents of the pc register is unchanged
*/
//SPHL | 1 | 5 | - - - - -
void pchl(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The specified byte is added to the con-
tents of the accumulator using two's copmlement arithmetic.
*/
//ADD | 1 | 4 | S Z A P C
void add(registers* registers, cpu_state* cpu_state, int _register);
//ADD_M | 1 | 4 | S Z A P C
void add_m(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The specified byte is subtracted from the con-
tents of the accumulator using two's copmlement arithmetic.
*/
//ADD | 1 | 4 | S Z A P C
void sub(registers* registers, cpu_state* cpu_state, int _register);
//ADD_M | 1 | 7 | S Z A P C
void sub_m(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The specified byte plus the contents of 
the Carry bit is added to the contents of the accumulator.
*/
//ADC | 1 | 4 | S Z A P C
void adc(registers* registers, cpu_state* cpu_state, int _register);
//ADC_M | 1 | 7 | S Z A P C
void adc_m(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: The Carry bit is internally added to the 
contents of the specified byte. This value is then subtracted
from the accumulator using two's complement arithmetic.
*/
//SBB | 1 | 4 | S Z A P C
void sbb(registers* registers, cpu_state* cpu_state, int _register);
//SBB_M | 1 | 7 | S Z A P C
void sbb_m(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Descriptoin: The specified byte is compared to the 
contents of the accumulator. The comparison is performed
by internally subtacting the contents of the REG from the ac-
cumulaotr (leaving both unchanged) and setting the cond-
tion bits according to the result. In particular, the Zero bit is
set if the qunatities are equal, and reset if they are unequal.
Since a subtact operation is performed, the Carry bit will be
set if there is no carry out of bit 7, indicating that the
contents of REG are greater than the contents of the accu-
mulator, and reset otherwise.
*/
//CMP | 1 | 4 | S Z A P C
void cmp(registers* registers, cpu_state* cpu_state, int _register);
//CMP_M | 1 | 7 | S Z A P C
void cmp_m(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: If the Carry Bit = 0, it is set to 1. If the Carry
bit = 1, it is reset to 0;
*/
//CMC | 1 | 4 - - - - C
void cmc(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Description: Each bit of the contents of the accumula-
tor is copmlemented (producing the one's complement).
*/
//CMA | 1 | 4 | - - - - -
void cma(registers* registers, cpu_state* cpu_state);

/* Intel 8080 Manual
Descriptoin: The program counter is incremented to
the address of the next sequential instruction. The CPU
then enters the STOPPPED state and no further activity takes
place until an interupt occurs
*/
//HLT | 1 | 7 | - - - - -
void hlt(registers* registers, cpu_state* cpu_state);

#endif //CPU_OPCODES_H 