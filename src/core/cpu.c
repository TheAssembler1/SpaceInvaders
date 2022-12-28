#include <headers.h>

void init_cpu(){
    log_info("initializing the cpu");

    regs = (registers*)malloc(sizeof(registers));
    cpu_st = (cpu_state*)malloc(sizeof(cpu_state));

    if (regs && cpu_st) {
        memset(regs, 0, sizeof(registers));
        memset(cpu_st, 0, sizeof(cpu_state));

        log_info("success setting up cpu");
    }
}

void deinit_cpu(){
    log_info("deinitializing the cpu");

    free(regs);
    free(cpu_st);
}

static void execute_opcode(uint16_t opcode){
    switch(opcode){
        case 0x00: nop(regs, cpu_st);                                break;
        case 0x01: lxi(regs, cpu_st, BC);                            break;
        case 0x02: stax(regs, cpu_st, BC);                           break;
        case 0x03: inx(regs, cpu_st, BC);                            break;
        case 0x06: mvi(regs, cpu_st, B);                             break;
        case 0x08: nop(regs, cpu_st);                                break;
        case 0x0A: ldax(regs, cpu_st, BC);                           break;
        case 0x10: nop(regs, cpu_st);                                break;
        case 0x11: lxi(regs, cpu_st, DE);                            break;
        case 0x12: stax(regs, cpu_st, DE);                           break;
        case 0x13: inx(regs, cpu_st, DE);                            break;
        case 0x16: mvi(regs, cpu_st, D);                             break;
        case 0x18: nop(regs, cpu_st);                                break;
        case 0x1A: ldax(regs, cpu_st, DE);                           break;
        case 0x20: nop(regs, cpu_st);                                break;
        case 0x21: lxi(regs, cpu_st, HL);                            break;
        case 0x22: shld(regs, cpu_st);                               break;
        case 0x23: inx(regs, cpu_st, HL);                            break;
        case 0x26: mvi(regs, cpu_st, H);                             break;
        case 0x28: nop(regs, cpu_st);                                break;
        case 0x2A: lhld(regs, cpu_st);                               break;
        case 0x30: nop(regs, cpu_st);                                break;
        case 0x31: lxi(regs, cpu_st, SP);                            break;
        case 0x32: sta(regs, cpu_st);                                break;
        case 0x33: inx(regs, cpu_st, SP);                            break;
        case 0x36: mvi_m(regs, cpu_st);                              break;
        case 0x38: nop(regs, cpu_st);                                break;
        case 0x3A: lda(regs, cpu_st);                                break;
        case 0xC2: jmp(regs, cpu_st, ZERO_DISTANCE, false, false);   break;
        case 0xC3: jmp(regs, cpu_st, false, false, true);            break;
        case 0xC4: call(regs, cpu_st, ZERO_DISTANCE, false, false);  break;
        case 0xCC: call(regs, cpu_st, ZERO_DISTANCE, true, false);   break;
        case 0xCD: call(regs, cpu_st, false, false, true);           break;
        case 0xCE: call(regs, cpu_st, false, false, true);           break;
        case 0xCF: call(regs, cpu_st, false, false, true);           break;
        case 0xD2: jmp(regs, cpu_st, CARRY_DISTANCE, false, false);  break;
        case 0xD4: call(regs, cpu_st, CARRY_DISTANCE, false, false); break;
        case 0xE2: jmp(regs, cpu_st, PARRY_DISTANCE, false, false);  break;
        case 0xF2: jmp(regs, cpu_st, SIGN_DISTANCE, false, false);   break;
        case 0xCA: jmp(regs, cpu_st, ZERO_DISTANCE, true, false);    break;
        case 0xCB: jmp(regs, cpu_st, false, false, true);            break;
        case 0xDA: jmp(regs, cpu_st, CARRY_DISTANCE, true, false);   break;
        case 0xDC: call(regs, cpu_st, CARRY_DISTANCE, true, false);  break;
        case 0xE4: call(regs, cpu_st, PARRY_DISTANCE, false, false); break;
        case 0xEA: jmp(regs, cpu_st, PARRY_DISTANCE, true, false);   break;
        case 0xEC: call(regs, cpu_st, PARRY_DISTANCE, true, false);  break;
        case 0xF4: call(regs, cpu_st, SIGN_DISTANCE, false, false);  break;
        case 0xFA: jmp(regs, cpu_st, SIGN_DISTANCE, true, false);    break;
        case 0xFC: call(regs, cpu_st, SIGN_DISTANCE, true, false);   break;
        default: 
            log_error("opcode %x does not exist", opcode); 
            deinit_manager(); 
            break;
    }
}

void run_next_opcode(){
    execute_opcode(read_byte_mem(regs->pc));
}

void load_register(int _register, uint8_t value){
    switch(_register){
        case A: regs->a = value; break; case F: regs->f = value; break;
        case B: regs->b = value; break; case C: regs->c = value; break;
        case D: regs->d = value; break; case E: regs->e = value; break;
        case H: regs->h = value; break; case L: regs->l = value; break;
        default: log_error("load register does not exist"); deinit_manager(); break;
    }
}

void load_pair_register(int pair_register, uint16_t value){
    switch(pair_register){
        case AF: regs->af = value; break;
        case BC: regs->bc = value; break;
        case DE: regs->de = value; break;
        case HL: regs->hl = value; break;
        case SP: regs->sp = value; break;
        default: log_error("load pair register does not exist"); deinit_manager(); break;
    }
}

uint8_t read_register(int _register){
    switch(_register){
        case A: return regs->a; break; case F: return regs->f; break;
        case B: return regs->b; break; case C: return regs->c; break;
        case D: return regs->d; break; case E: return regs->e; break;
        case H: return regs->h; break; case L: return regs->l; break;
        default: log_error("read register does not exist"); deinit_manager(); break;
    }
}

uint16_t read_pair_register(int pair_register){
    switch(pair_register){
        case AF: return regs->af; break;
        case BC: return regs->bc; break;
        case DE: return regs->de; break;
        case HL: return regs->hl; break;
        case SP: return regs->sp; break;
        default: log_error("read pair register does not exist"); deinit_manager(); break;
    }
}