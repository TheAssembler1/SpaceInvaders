#ifndef CPU_OPCODES_H
#define CPU_OPCODES_H

#include <log.h>
#include <cpu.h>

struct registers regs;
struct cpu_state cpu;

/* Intel 8080 Manual
Description: No operation occurs. Execution proceeds
with the next sequential instruction.
*/
//NOP | 1 | 4 | - - - - -
void nop(int selector);

/* Intel 8080 Manual
Description: The specified register or memory byte is
incremented by one
*/
//INR | 1 | 5 | S Z A P -
void inr(int selector);

#endif
