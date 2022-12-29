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
    init_mem();
    init_gpu();

    test(regs);

    cycle_machine();
}

static void cycle_machine() {
    bool run_machine = true;

    SDL_Event event;

    while (run_machine) {
        run_next_opcode();
        render_screen(renderer, cpu_st);

        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            run_machine = false;
    }

    deinit_manager();
}

void deinit_manager(){
    deinit_cpu();
    deinit_mem();
    deinit_gpu();

    //deiniting sdl
    SDL_Quit();

    //exiting here instead of in main
    exit(0);
}