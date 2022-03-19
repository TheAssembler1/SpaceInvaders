#include <headers.h>

struct registers* regs;
struct cpu_state* cpu;

void init_cpu(){
    log_info("initializing the cpu");

    regs = (struct registers*)malloc(sizeof(struct registers));
    cpu = (struct cpu_state*)malloc(sizeof(struct cpu_state));

    if(regs && cpu)
        log_info("success setting up cpu");
}

void execute_opcode(uint16_t opcode){
    log_info("Running %u", opcode);

    switch(opcode){
        case 0x00: nop(); break;
    }
    /* Intel 8080 Manual
    Description: The specified register or memory byte is
    incremented by one
    */
    //INR | 1 | 5 | S Z A P -
}