#include <headers.h>

static void cycle_machine();

void init_manager(){
    //initing sdl
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        log_error("error initializing SDL: %s\n", SDL_GetError());
    else
        log_info("success initializing SDL");

    //initing sdl_ttf
    TTF_Init();

    init_cpu();
    init_mem(false, NULL);
    init_gpu();

    test(regs);

    cycle_machine();
}
/*
 02AA D677      C020:	SUI	077H	;A=89H,C=1,P=0,S=1,Z=0
 02AC D4A006    	CNC	CPUER	;TEST "CNC"
 02AF ECA006    	CPE	CPUER	;TEST "CPE"
 02B2 F4A006    	CP	CPUER	;TEST "CP"
 02B5 CCA006    	CZ	CPUER	;TEST "CZ"
*/
static void cycle_test_machine() {
    while (regs->pc != 0x00) {
        if (regs->pc == 0x0005) {
            if (regs->c == 0x02) {
                log_log_nonewl("%c", regs->e);
            }
            else if (regs->c == 0x09) {
                while (read_byte_mem(regs->de) != '$') {
                    log_log_nonewl("%c", read_byte_mem(regs->de));
                    regs->de++;
                }
            }
            else {
                log_error("Unknown c in test interrupt");
                deinit_test_manager();
            }

            
            ret(regs, cpu_st, ALWAYS_DISTANCE, false);
        }

        run_next_opcode();
    }
}

void init_test_manager() {
    //initing sdl
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        log_error("error initializing SDL: %s\n", SDL_GetError());
    else
        log_info("success initializing SDL");

    init_cpu();
    init_mem(true, "TST8080.COM");


    regs->pc = 0x100;
    regs->sp = 0xFFFF;

    cycle_test_machine();
}

void deinit_test_manager() {
    log_log();
    deinit_cpu();
    deinit_mem();

    SDL_Quit();

    //exiting here instead of in main
    exit(0);
}

static void cycle_machine() {
    bool run_machine = true;

    SDL_Event event;

    while (run_machine) {
        cpu_st->cycles = 0;

        while(cpu_st->cycles < CYCLES_PER_FRAME)
            run_next_opcode();
        execute_interrupt(HALFWAY_INTERRUPT);

        while (cpu_st->cycles < CYCLES_PER_FRAME * 2)
            run_next_opcode();
        execute_interrupt(FULL_INTERRUPT);

        render_screen(renderer);

        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            run_machine = false;
    }

    deinit_manager();
}

void deinit_manager(){
    print_cpu();

    deinit_cpu();
    deinit_mem();
    deinit_gpu();

    //deiniting sdl
    SDL_Quit();

    //exiting here instead of in main
    exit(0);
}