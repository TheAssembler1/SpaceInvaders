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
#define ALWAYS_DISTANCE 8

#define BOOL(x) (!(!(x)))

#define BIT_SET(arg,posn) ((arg) | (1L << (posn)))
#define BIT_CLEAR(arg,posn) ((arg) & ~(1L << (posn)))
#define BIT_TEST(arg,posn) BOOL((arg) & (1L << (posn)))
#define BIT_FLIP(arg,posn) ((arg) ^ (1L << (posn)))

//FIXME: Changing this to 400000 breaks with interrupts. something is def wrong here.
#define CYCLES_PER_SECOND  2000000
#define CYCLES_PER_FRAME CYCLES_PER_SECOND / 60

struct _registers{
    union{
        struct{
            uint8_t f;
            uint8_t a;
        };
        uint16_t af;
    };
    
    union{
        struct{
            uint8_t c;
            uint8_t b;
        };
        uint16_t bc;
    };

    union{
        struct{
            uint8_t e;
            uint8_t d;
        };
        uint16_t de;
    };

    union{
        struct{
            uint8_t l;
            uint8_t h;
        };
        uint16_t hl;
    };

    uint16_t sp;
    uint16_t pc;
};

typedef struct _registers registers;

struct _cpu_state{
    long double cycles;
    bool interrupts_enabled;
    bool halted;
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

void print_cpu();

void execute_interrupt(uint16_t opcode);

void print_bits(int size, uint16_t value);

#endif //CPU_H
