#ifndef CPU_H
#define CPU_H

#define SIGN      0b10000000
#define ZERO      0b01000000
#define AUX_CARRY 0b00010000
#define PARRY     0b00000010
#define CARRY     0b00000001

#define SIGN_DISTANCE 7
#define ZERO_DISTANCE 6
#define AUX_CARRY_DISTANCE 4
#define PARRY_DISTANCE 1
#define CARRY_DISTANCE 0

#define BOOL(x) (!(!(x)))

#define BIT_SET(arg,posn) ((arg) | (1L << (posn)))
#define BIT_CLEAR(arg,posn) ((arg) & ~(1L << (posn)))
#define BIT_TEST(arg,posn) BOOL((arg) & (1L << (posn)))
#define BIT_FLIP(arg,posn) ((arg) ^ (1L << (posn)))


struct _registers{
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

typedef struct _registers registers;

struct _cpu_state{
    unsigned long cycles;
};

typedef struct _cpu_state cpu_state;

enum registers_select{
    A, F,
    B, C,
    D, E,
    H, L
};

enum pair_registers_select{
    AF,
    BC,
    DE,
    HL,
    SP,
    PC
};

extern registers* regs;
extern cpu_state* cpu_st;

void init_cpu();
void deinit_cpu();

void run_next_opcode();

void load_register(int _register, uint8_t value);
void load_pair_register(int pair_register, uint16_t value);

uint8_t read_register(int _register);
uint16_t read_pair_register(int pair_register);

//NOTE: This takes what flags to check set ORd together
void check_set_flags(registers* registers, uint8_t flags, uint8_t intial, uint16_t result);

#endif //CPU_H
