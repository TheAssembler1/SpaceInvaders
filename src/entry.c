#include <headers.h>

int main(int argc, char* argv[]) {
    //initing sdl
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        log_error("error initializing SDL: %s\n", SDL_GetError());
    else
        log_info("success initializing SDL");

    init_manager();
    deinit_manager();

    //should never hit here should return inside deinit_manager
    log_error("returning from main");

    return -1;
}