#include <headers.h>

int main(int argc, char* argv[]) {
    //initing sdl
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        log_error("error intializing SDL: %s\n", SDL_GetError());

    init_manager();
    deinit_manager();

    //should never hit here should return inside deinit_manager
    log_error("returning from main");
    return -1;
}