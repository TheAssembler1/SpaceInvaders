#ifndef CPU_OPCODES_H
#define CPU_OPCODES_H

#include <log.h>
#include <cpu.h>

struct registers;
struct cpu_state;

//NOP | 1 | 4 | - - - - -
void nop(struct registers* reg, struct cpu_state* cpu);

#endif
