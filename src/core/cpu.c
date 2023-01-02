#include <headers.h>

registers* regs;
cpu_state* cpu_st;

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

    print_cpu();

    free(regs);
    free(cpu_st);
}

static void execute_opcode(uint16_t opcode) {
	if (cpu_st->halted)
		return;

	switch (opcode) {
	case 0x00: nop(regs, cpu_st);                                break;
	case 0x01: lxi(regs, cpu_st, BC);                            break;
	case 0x02: stax(regs, cpu_st, BC);                           break;
	case 0x03: inx(regs, cpu_st, BC);                            break;
	case 0x04: inr(regs, cpu_st, B);                             break;
	case 0x05: dcr(regs, cpu_st, B);                             break;
	case 0x06: mvi(regs, cpu_st, B);                             break;
	case 0x07: rlc(regs, cpu_st);                                break;
	case 0x08: nop(regs, cpu_st);                                break;
	case 0x09: dad(regs, cpu_st, BC);                            break;
	case 0x0A: ldax(regs, cpu_st, BC);                           break;
	case 0x0B: dcx(regs, cpu_st, BC);                            break;
	case 0x0C: inr(regs, cpu_st, C);							 break;
	case 0x0D: dcr(regs, cpu_st, C);                             break;
	case 0x0E: mvi(regs, cpu_st, C);                             break;
	case 0x0F: rrc(regs, cpu_st);                                break;
	case 0x10: nop(regs, cpu_st);                                break;
	case 0x11: lxi(regs, cpu_st, DE);                            break;
	case 0x12: stax(regs, cpu_st, DE);                           break;
	case 0x13: inx(regs, cpu_st, DE);                            break;
	case 0x14: inr(regs, cpu_st, D);                             break;
	case 0x15: dcr(regs, cpu_st, D);                             break;
	case 0x16: mvi(regs, cpu_st, D);                             break;
	case 0x17: ral(regs, cpu_st);                                break;
	case 0x18: nop(regs, cpu_st);                                break;
	case 0x19: dad(regs, cpu_st, DE);                            break;
	case 0x1A: ldax(regs, cpu_st, DE);                           break;
	case 0x1B: dcx(regs, cpu_st, DE);                            break;
	case 0x1C: inr(regs, cpu_st, E);							 break;
	case 0x1D: dcr(regs, cpu_st, E);                             break;
	case 0x1E: mvi(regs, cpu_st, E);                             break;
	case 0x1F: rar(regs, cpu_st);                                break;
	case 0x20: nop(regs, cpu_st);                                break;
	case 0x21: lxi(regs, cpu_st, HL);                            break;
	case 0x22: shld(regs, cpu_st);                               break;
	case 0x23: inx(regs, cpu_st, HL);                            break;
	case 0x24: inr(regs, cpu_st, H);                             break;
	case 0x25: dcr(regs, cpu_st, H);                             break;
	case 0x26: mvi(regs, cpu_st, H);                             break;
	case 0x27: daa(regs, cpu_st);                                break;
	case 0x28: nop(regs, cpu_st);                                break;
	case 0x29: dad(regs, cpu_st, HL);                            break;
	case 0x2A: lhld(regs, cpu_st);                               break;
	case 0x2B: dcx(regs, cpu_st, HL);                            break;
	case 0x2C: inr(regs, cpu_st, L);							 break;
	case 0x2D: dcr(regs, cpu_st, L);                             break;
	case 0x2E: mvi(regs, cpu_st, L);                             break;
	case 0x2F: cma(regs, cpu_st);								 break;
	case 0x30: nop(regs, cpu_st);                                break;
	case 0x31: lxi(regs, cpu_st, SP);                            break;
	case 0x32: sta(regs, cpu_st);                                break;
	case 0x33: inx(regs, cpu_st, SP);                            break;
	case 0x34: inr_m(regs, cpu_st);                              break;
	case 0x35: dcr_m(regs, cpu_st);                              break;
	case 0x36: mvi_m(regs, cpu_st);                              break;
	case 0x37: stc(regs, cpu_st);                                break;
	case 0x38: nop(regs, cpu_st);                                break;
	case 0x39: dad(regs, cpu_st, SP);                            break;
	case 0x3A: lda(regs, cpu_st);                                break;
	case 0x3B: dcx(regs, cpu_st, SP);                            break;
	case 0x3C: inr(regs, cpu_st, A);							 break;
	case 0x3D: dcr(regs, cpu_st, A);                             break;
	case 0x3E: mvi(regs, cpu_st, A);                             break;
	case 0x3F: cmc(regs, cpu_st);								 break;
	case 0x40: mov(regs, cpu_st, B, B);                          break;
	case 0x41: mov(regs, cpu_st, B, C);                          break;
	case 0x42: mov(regs, cpu_st, B, D);                          break;
	case 0x43: mov(regs, cpu_st, B, E);                          break;
	case 0x44: mov(regs, cpu_st, B, H);                          break;
	case 0x45: mov(regs, cpu_st, B, L);                          break;
	case 0x46: mov_m(regs, cpu_st, B, false);                    break;
	case 0x47: mov(regs, cpu_st, B, A);                          break;
	case 0x48: mov(regs, cpu_st, C, B);                          break;
	case 0x49: mov(regs, cpu_st, C, C);                          break;
	case 0x4A: mov(regs, cpu_st, C, D);                          break;
	case 0x4B: mov(regs, cpu_st, C, E);                          break;
	case 0x4C: mov(regs, cpu_st, C, H);                          break;
	case 0x4D: mov(regs, cpu_st, C, L);                          break;
	case 0x4E: mov_m(regs, cpu_st, C, false);                    break;
	case 0x4F: mov(regs, cpu_st, C, A);                          break;
	case 0x50: mov(regs, cpu_st, D, B);                          break;
	case 0x51: mov(regs, cpu_st, D, C);                          break;
	case 0x52: mov(regs, cpu_st, D, D);                          break;
	case 0x53: mov(regs, cpu_st, D, E);                          break;
	case 0x54: mov(regs, cpu_st, D, H);                          break;
	case 0x55: mov(regs, cpu_st, D, L);                          break;
	case 0x56: mov_m(regs, cpu_st, D, false);                    break;
	case 0x57: mov(regs, cpu_st, D, A);                          break;
	case 0x58: mov(regs, cpu_st, E, B);                          break;
	case 0x59: mov(regs, cpu_st, E, C);                          break;
	case 0x5A: mov(regs, cpu_st, E, D);                          break;
	case 0x5B: mov(regs, cpu_st, E, E);                          break;
	case 0x5C: mov(regs, cpu_st, E, H);                          break;
	case 0x5D: mov(regs, cpu_st, E, L);                          break;
	case 0x5E: mov_m(regs, cpu_st, E, false);                    break;
	case 0x5F: mov(regs, cpu_st, E, A);                          break;
	case 0x60: mov(regs, cpu_st, H, B);                          break;
	case 0x61: mov(regs, cpu_st, H, C);                          break;
	case 0x62: mov(regs, cpu_st, H, D);                          break;
	case 0x63: mov(regs, cpu_st, H, E);                          break;
	case 0x64: mov(regs, cpu_st, H, H);                          break;
	case 0x65: mov(regs, cpu_st, H, L);                          break;
	case 0x66: mov_m(regs, cpu_st, H, false);                    break;
	case 0x67: mov(regs, cpu_st, H, A);                          break;
	case 0x68: mov(regs, cpu_st, L, B);                          break;
	case 0x69: mov(regs, cpu_st, L, C);                          break;
	case 0x6A: mov(regs, cpu_st, L, D);                          break;
	case 0x6B: mov(regs, cpu_st, L, E);                          break;
	case 0x6C: mov(regs, cpu_st, L, H);                          break;
	case 0x6D: mov(regs, cpu_st, L, L);                          break;
	case 0x6E: mov_m(regs, cpu_st, L, false);                    break;
	case 0x6F: mov(regs, cpu_st, L, A);                          break;
	case 0x70: mov_m(regs, cpu_st, B, true);                     break;
	case 0x71: mov_m(regs, cpu_st, C, true);                     break;
	case 0x72: mov_m(regs, cpu_st, D, true);                     break;
	case 0x73: mov_m(regs, cpu_st, E, true);                     break;
	case 0x74: mov_m(regs, cpu_st, H, true);                     break;
	case 0x75: mov_m(regs, cpu_st, L, true);                     break;
	case 0x76: hlt(regs, cpu_st);								 break;
	case 0x77: mov_m(regs, cpu_st, A, true);                     break;
	case 0x78: mov(regs, cpu_st, A, B);                          break;
	case 0x79: mov(regs, cpu_st, A, C);                          break;
	case 0x7A: mov(regs, cpu_st, A, D);                          break;
	case 0x7B: mov(regs, cpu_st, A, E);                          break;
	case 0x7C: mov(regs, cpu_st, A, H);                          break;
	case 0x7D: mov(regs, cpu_st, A, L);                          break;
	case 0x7E: mov_m(regs, cpu_st, A, false);                    break;
	case 0x7F: mov(regs, cpu_st, A, A);                          break;
	case 0x80: add(regs, cpu_st, B); break;
	case 0x81: add(regs, cpu_st, C); break;
	case 0x82: add(regs, cpu_st, D); break;
	case 0x83: add(regs, cpu_st, E); break;
	case 0x84: add(regs, cpu_st, H); break;
	case 0x85: add(regs, cpu_st, L); break;
	case 0x86: add_m(regs, cpu_st);  break;
	case 0x87: add(regs, cpu_st, A); break;
	case 0x88: adc(regs, cpu_st, B); break;
	case 0x89: adc(regs, cpu_st, C); break;
	case 0x8A: adc(regs, cpu_st, D); break;
	case 0x8B: adc(regs, cpu_st, E); break;
	case 0x8C: adc(regs, cpu_st, H); break;
	case 0x8D: adc(regs, cpu_st, L); break;
	case 0x8E: adc_m(regs, cpu_st);  break;
	case 0x8F: adc(regs, cpu_st, A); break;
	case 0x90: sub(regs, cpu_st, B); break;
	case 0x91: sub(regs, cpu_st, C); break;
	case 0x92: sub(regs, cpu_st, D); break;
	case 0x93: sub(regs, cpu_st, E); break;
	case 0x94: sub(regs, cpu_st, H); break;
	case 0x95: sub(regs, cpu_st, L); break;
	case 0x96: sub_m(regs, cpu_st);  break;
	case 0x97: sub(regs, cpu_st, A); break;
	case 0x98: sbb(regs, cpu_st, B); break;
	case 0x99: sbb(regs, cpu_st, C); break;
	case 0x9A: sbb(regs, cpu_st, D); break;
	case 0x9B: sbb(regs, cpu_st, E); break;
	case 0x9C: sbb(regs, cpu_st, H); break;
	case 0x9D: sbb(regs, cpu_st, L); break;
	case 0x9E: sbb_m(regs, cpu_st);  break;
	case 0x9F: sbb(regs, cpu_st, A); break;
	case 0xA0: ana(regs, cpu_st, B);                             break;
	case 0xA1: ana(regs, cpu_st, C);                             break;
	case 0xA2: ana(regs, cpu_st, D);                             break;
	case 0xA3: ana(regs, cpu_st, E);                             break;
	case 0xA4: ana(regs, cpu_st, H);                             break;
	case 0xA5: ana(regs, cpu_st, L);                             break;
	case 0xA6: ana_m(regs, cpu_st);                              break;
	case 0xA7: ana(regs, cpu_st, A);                             break;
	case 0xA8: xra(regs, cpu_st, B);                             break;
	case 0xA9: xra(regs, cpu_st, C);                             break;
	case 0xAA: xra(regs, cpu_st, D);                             break;
	case 0xAB: xra(regs, cpu_st, E);                             break;
	case 0xAC: xra(regs, cpu_st, H);                             break;
	case 0xAD: xra(regs, cpu_st, L);                             break;
	case 0xAE: xra_m(regs, cpu_st);                              break;
	case 0xAF: xra(regs, cpu_st, A);                             break;
	case 0xB0: ora(regs, cpu_st, B);                             break;
	case 0xB1: ora(regs, cpu_st, C);                             break;
	case 0xB2: ora(regs, cpu_st, D);                             break;
	case 0xB3: ora(regs, cpu_st, E);                             break;
	case 0xB4: ora(regs, cpu_st, H);                             break;
	case 0xB5: ora(regs, cpu_st, L);                             break;
	case 0xB6: ora_m(regs, cpu_st);                              break;
	case 0xB7: ora(regs, cpu_st, A);                             break;
	case 0xB8: cmp(regs, cpu_st, B);                             break;
	case 0xB9: cmp(regs, cpu_st, C);                             break;
	case 0xBA: cmp(regs, cpu_st, D);                             break;
	case 0xBB: cmp(regs, cpu_st, E);                             break;
	case 0xBC: cmp(regs, cpu_st, H);                             break;
	case 0xBD: cmp(regs, cpu_st, L);                             break;
	case 0xBE: cmp_m(regs, cpu_st);                              break;
	case 0xBF: cmp(regs, cpu_st, A);                             break;
	case 0xC0: ret(regs, cpu_st, !BIT_TEST(regs->f, ZERO_DISTANCE));          break;
	case 0xC1: pop(regs, cpu_st, BC);										  break;
	case 0xC2: jmp(regs, cpu_st, !BIT_TEST(regs->f, ZERO_DISTANCE));          break;
	case 0xC3: jmp(regs, cpu_st, true);										  break;
	case 0xC4: call(regs, cpu_st, !BIT_TEST(regs->f, ZERO_DISTANCE));         break;
	case 0xC5: push(regs, cpu_st, BC);									      break;
	case 0xC6: adi(regs, cpu_st);										      break;
	case 0xC7: rst(regs, cpu_st, 0b0000000000000000);					      break;
	case 0xC8: ret(regs, cpu_st, BIT_TEST(regs->f, ZERO_DISTANCE));           break;
	case 0xC9: ret(regs, cpu_st, true);										  break;
	case 0xCA: jmp(regs, cpu_st, BIT_TEST(regs->f, ZERO_DISTANCE));           break;
	case 0xCB: jmp(regs, cpu_st, true);										  break;
	case 0xCC: call(regs, cpu_st, BIT_TEST(regs->f, ZERO_DISTANCE));          break;
	case 0xCD: call(regs, cpu_st, true);								      break;
	case 0xCE: aci(regs, cpu_st);										      break;
	case 0xCF: rst(regs, cpu_st, 0b0000000000001000);						  break;
	case 0xD0: ret(regs, cpu_st, !BIT_TEST(regs->f, CARRY_DISTANCE));         break;
	case 0xD1: pop(regs, cpu_st, DE);								          break;
	case 0xD2: jmp(regs, cpu_st, !BIT_TEST(regs->f, CARRY_DISTANCE));         break;
	case 0xD3: out(regs, cpu_st);                                             break;
	case 0xD4: call(regs, cpu_st, !BIT_TEST(regs->f, CARRY_DISTANCE));        break;
	case 0xD5: push(regs, cpu_st, DE);										  break;
	case 0xD6: sui(regs, cpu_st);											  break;
	case 0xD7: rst(regs, cpu_st, 0b0000000000010000);						  break;
	case 0xD8: ret(regs, cpu_st, BIT_TEST(regs->f, CARRY_DISTANCE));          break;
	case 0xD9: ret(regs, cpu_st, true);										  break;
	case 0xDA: jmp(regs, cpu_st, BIT_TEST(regs->f, CARRY_DISTANCE));          break;
	case 0xDB: in(regs, cpu_st);											  break;
	case 0xDC: call(regs, cpu_st, BIT_TEST(regs->f, CARRY_DISTANCE));         break;
	case 0xDD: call(regs, cpu_st, true);									  break;
	case 0xDE: sbi(regs, cpu_st);											  break;
	case 0xDF: rst(regs, cpu_st, 0b0000000000011000);						  break;
	case 0xE0: ret(regs, cpu_st, !BIT_TEST(regs->f, PARRY_DISTANCE));         break;
	case 0xE1: pop(regs, cpu_st, HL);										  break;
	case 0xE2: jmp(regs, cpu_st, !BIT_TEST(regs->f, PARRY_DISTANCE));         break;
	case 0xE3: xthl(regs, cpu_st);											  break;
	case 0xE4: call(regs, cpu_st, !BIT_TEST(regs->f, PARRY_DISTANCE));        break;
	case 0xE5: push(regs, cpu_st, HL);									      break;
	case 0xE6: ani(regs, cpu_st);											  break;
	case 0xE7: rst(regs, cpu_st, 0b0000000000100000);						  break;
	case 0xE8: ret(regs, cpu_st, BIT_TEST(regs->f, PARRY_DISTANCE));          break;
	case 0xE9: pchl(regs, cpu_st);											  break;
	case 0xEA: jmp(regs, cpu_st, BIT_TEST(regs->f, PARRY_DISTANCE));          break;
	case 0xEB: xchg(regs, cpu_st);											  break;
	case 0xEC: call(regs, cpu_st, BIT_TEST(regs->f, PARRY_DISTANCE));         break;
	case 0xED: call(regs, cpu_st, true);									  break;
	case 0xEF: rst(regs, cpu_st, 0b0000000000101000);						  break;
	case 0xEE: xri(regs, cpu_st);											  break;
	case 0xF0: ret(regs, cpu_st, !BIT_TEST(regs->f, SIGN_DISTANCE));          break;
	case 0xF1: pop(regs, cpu_st, AF);										  break;
	case 0xF2: jmp(regs, cpu_st, !BIT_TEST(regs->f, SIGN_DISTANCE));          break;
	case 0xF3: di(regs, cpu_st);											  break;
	case 0xF4: call(regs, cpu_st, !BIT_TEST(regs->f, SIGN_DISTANCE));         break;
	case 0xF5: push(regs, cpu_st, AF);										  break;
	case 0xF6: ori(regs, cpu_st);											  break;
	case 0xF7: rst(regs, cpu_st, 0b0000000000110000);						  break;
	case 0xF8: ret(regs, cpu_st, BIT_TEST(regs->f, SIGN_DISTANCE));           break;
	case 0xF9: sphl(regs, cpu_st);											  break;
	case 0xFA: jmp(regs, cpu_st, BIT_TEST(regs->f, SIGN_DISTANCE));           break;
	case 0xFB: ei(regs, cpu_st);											  break;
	case 0xFC: call(regs, cpu_st, BIT_TEST(regs->f, SIGN_DISTANCE));          break;
	case 0xFD: call(regs, cpu_st, true);									  break;
	case 0xFE: cpi(regs, cpu_st);											  break;
	case 0xFF: rst(regs, cpu_st, 0b0000000000111000);						  break;
	default:
		log_error("opcode %x does not exist", opcode);
		deinit_manager();
		break;
	}

	//log_log("%x", current_pc);
	//print_cpu();
}

void execute_interrupt(uint16_t opcode) {
    if (cpu_st->interrupts_enabled) {
		cpu_st->halted = false;
        execute_opcode(opcode);
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

static int parity_array[256] = {1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
                                0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
                                0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
                                1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
                                0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
                                1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
                                1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
                                0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1};

#define OVERFLOW 0xFF
#define FLAG_TO_SET 0x01
#define FLAG_TO_CLEAR 0x05
#define FLAG_TO_CLEAR_AGAIN 0x03

void check_set_flags(registers* registers, uint8_t flags, uint8_t initial, uint16_t result) {
	if (BIT_TEST(flags, SIGN_DISTANCE)) {
        if (BIT_TEST((uint8_t)result, SIGN_DISTANCE)){
			registers->f = BIT_SET(registers->f, SIGN_DISTANCE);
		}else
		{
			registers->f = BIT_CLEAR(registers->f, SIGN_DISTANCE);
		}
    }

    if (BIT_TEST(flags, ZERO_DISTANCE)) {
        if (!(uint8_t)result) {
			registers->f = BIT_SET(registers->f, ZERO_DISTANCE);
		}
        else{
			registers->f = BIT_CLEAR(registers->f, ZERO_DISTANCE);
		}
    }

    if (BIT_TEST(flags, AUX_CARRY_DISTANCE)) {
        if (~(registers->a ^ initial ^ (uint8_t)result) & 0x10){
			registers->f = BIT_SET(registers->f, AUX_CARRY_DISTANCE);
		}
		else{
			registers->f = BIT_CLEAR(registers->f, AUX_CARRY_DISTANCE);
		}
    }

    if (BIT_TEST(flags, PARRY_DISTANCE)) {
        if (parity_array[(uint8_t)result]){
			registers->f = BIT_SET(registers->f, PARRY_DISTANCE);
		}
        else{
			registers->f = BIT_CLEAR(registers->f, PARRY_DISTANCE);
		}
    }

    if (BIT_TEST(flags, CARRY_DISTANCE)) {
        if (result > OVERFLOW){
			registers->f = BIT_SET(registers->f, CARRY_DISTANCE);
		}
        else{
			registers->f = BIT_CLEAR(registers->f, CARRY_DISTANCE);
		}
    }

	registers->f = BIT_CLEAR(registers->f, FLAG_TO_CLEAR);
	registers->f = BIT_CLEAR(registers->f, FLAG_TO_CLEAR_AGAIN);
	registers->f = BIT_SET(registers->f, FLAG_TO_SET);
}

void print_bits(int size, uint16_t value){
    for (int i = (size * 8) - 1; i >= 0; i--) {
        if (i != (size * 8) - 1 && (i + 1) % 8 == 0)
            log_log_nonewl(" ");

        if (BIT_TEST(value, i))
            log_log_nonewl("1");
        else
            log_log_nonewl("0");
    }
}

void print_cpu() {
    log_trace("Begin printing cpu");
    log_log("------------------------------");

    log_log_nonewl("PC: ");
    print_bits(sizeof(uint16_t), regs->pc);
    log_log(" | 0x%04X", regs->pc);

    log_log_nonewl("SP: ");
    print_bits(sizeof(uint16_t), regs->sp);
    log_log(" | 0x%04X", regs->sp);

    log_log_nonewl("AF: ");
    print_bits(sizeof(uint16_t), regs->af);
    log_log(" | 0x%04X | 0x%02x | 0x%02x", regs->af, regs->a, regs->f);


    log_log_nonewl("BC: ");
    print_bits(sizeof(uint16_t), regs->bc);
    log_log(" | 0x%04X | 0x%02x | 0x%02x", regs->bc, regs->b, regs->c);

    log_log_nonewl("DE: ");
    print_bits(sizeof(uint16_t), regs->de);
    log_log(" | 0x%04X | 0x%02x | 0x%02x", regs->de, regs->d, regs->e);

    log_log_nonewl("HL: ");
    print_bits(sizeof(uint16_t), regs->hl);
    log_log(" | 0x%04X | 0x%02x | 0x%02x", regs->hl, regs->h, regs->l);

    log_log_nonewl("SIGN FLAG: ");
    (BIT_TEST(regs->f, SIGN_DISTANCE)) ? log_log("     1") : log_log("     0");
    log_log_nonewl("ZERO FLAG: ");
    (BIT_TEST(regs->f, ZERO_DISTANCE)) ? log_log("     1") : log_log("     0");
    log_log_nonewl("AUX CARRY FLAG: ");
    (BIT_TEST(regs->f, AUX_CARRY_DISTANCE)) ? log_log("1") : log_log("0");
    log_log_nonewl("PARRY FLAG: ");
    (BIT_TEST(regs->f, PARRY_DISTANCE)) ? log_log("    1") : log_log("    0");
    log_log_nonewl("CARRY FLAG: ");
    (BIT_TEST(regs->f, CARRY_DISTANCE)) ? log_log("    1") : log_log("    0");

    log_log("------------------------------");
    log_trace("End printing cpu");
}

uint8_t rotl(uint8_t value)
{
	return((value << 1) | (value >> 7));
}

uint8_t rotr(uint8_t value)
{
	return((value >> 1) | (value << 7));
}