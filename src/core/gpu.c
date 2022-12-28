#include <headers.h>

TTF_Font* font;

void init_gpu() {
	log_info("initializing the gpu");

	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	SDL_RenderClear(renderer);
}

void deinit_gpu() {
	log_info("deinitializing the gpu");

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void render_screen(SDL_Renderer* renderer) {
	SDL_RenderClear(renderer);

	//render pixel buffer here

	SDL_RenderPresent(renderer);
}