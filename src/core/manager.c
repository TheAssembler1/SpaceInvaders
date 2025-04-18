#include <headers.h>

static void cycle_machine();

void init_manager() {
    // initing sdl
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        log_error("error initializing SDL: %s\n", SDL_GetError());
    else
        log_info("success initializing SDL");

    init_cpu();
    init_mem(false, NULL);
    init_gpu();

    test(regs);

    cycle_machine();
}

static void cycle_test_machine() {
    log_log();

    while (regs->pc != 0x00) {
        if (regs->pc == 0x0005) {
            if (regs->c == 0x02) {
                log_log_nonewl("%c", regs->e);
            } else if (regs->c == 0x09) {
                while (read_byte_mem(regs->de) != '$') {
                    log_log_nonewl("%c", read_byte_mem(regs->de));
                    regs->de++;
                }
            } else {
                log_error("Unknown c in test interrupt");
                deinit_test_manager();
            }
            ret(regs, cpu_st, true);
        }
        run_next_opcode();
    }

    log_log();
}

void init_test_manager() {
    // initing sdl
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        log_error("error initializing SDL: %s\n", SDL_GetError());
    else
        log_info("success initializing SDL");

    init_cpu();
    init_mem(true, "8080EXM.COM");

    regs->pc = 0x100;
    regs->sp = 0xFFFF;

    cycle_test_machine();
}

void deinit_test_manager() {
    log_log();
    deinit_cpu();
    deinit_mem();

    SDL_Quit();

    // exiting here instead of in main
    exit(0);
}

#define TICK_INTERVAL 15

static uint32_t next_time;

uint32_t time_left() {
    uint32_t now;

    now = SDL_GetTicks();
    if (next_time <= now)
        return 0;
    else
        return next_time - now;
}

bool inputs[NUM_INPUTS];

static void cycle_machine() {
    bool run_machine = true;

    SDL_Event event;

    next_time = SDL_GetTicks() + TICK_INTERVAL;
    while (run_machine) {
        cpu_st->cycles = 0;

        while (cpu_st->cycles < CYCLES_PER_FRAME)
            run_next_opcode();
        execute_interrupt(HALFWAY_INTERRUPT);

        while (cpu_st->cycles < CYCLES_PER_FRAME * 2)
            run_next_opcode();
        execute_interrupt(FULL_INTERRUPT);

        render_screen(renderer);

        if (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                run_machine = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode == SDL_SCANCODE_A) {
                    inputs[A_KEY] = true;
                } else if (event.key.keysym.scancode == SDL_SCANCODE_D) {
                    inputs[D_KEY] = true;
                } else if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                    inputs[SPACE] = true;
                } else if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
                    inputs[INSERT_COIN] = true;
                } else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    run_machine = false;
                }
                break;

            case SDL_KEYUP:
                if (event.key.keysym.scancode == SDL_SCANCODE_A) {
                    inputs[A_KEY] = false;
                } else if (event.key.keysym.scancode == SDL_SCANCODE_D) {
                    inputs[D_KEY] = false;
                } else if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                    inputs[SPACE] = false;
                } else if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
                    inputs[INSERT_COIN] = false;
                }
                break;
            }
        }

        SDL_Delay(time_left());
        next_time += TICK_INTERVAL;
    }

    deinit_manager();
}

void deinit_manager() {
    print_cpu();

    deinit_cpu();
    deinit_mem();
    deinit_gpu();

    // deiniting sdl
    SDL_Quit();

    // exiting here instead of in main
    exit(0);
}
