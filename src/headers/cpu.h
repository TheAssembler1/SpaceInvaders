#ifndef CPU_H
#define CPU_H

struct registers{
    union{
        struct{
            uint8_t a;
            uint8_t f;
        };
        uint16_t af;
    };
    
    union{
        struct{
            uint8_t b;
            uint8_t c;
        };
        uint16_t bc;
    };

    union{
        struct{
            uint8_t d;
            uint8_t e;
        };
        uint16_t de;
    };

    union{
        struct{
            uint8_t h;
            uint8_t l;
        };
        uint16_t hl;
    };

    uint16_t sp;
    uint16_t pc;
};

struct cpu_state{
    unsigned long cycles;
};

enum flags{
    SIGN =      0b10000000,
    ZERO =      0b01000000,
    AUX_CARRY = 0b00010000,
    PARRY =     0b00000010,
    CARRY =     0b00000001
};

enum registers_select{
    A, F,
    B, C,
    D, E,
    H, L
};

void init_cpu();
void execute_opcode(uint16_t opcode);

void log_cpu();

#endif
