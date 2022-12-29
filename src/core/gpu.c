#include <headers.h>

TTF_Font* font;
SDL_Renderer* renderer;
SDL_Window* window;

void init_gpu() {
	log_info("initializing the gpu");

	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	SDL_RenderClear(renderer);
}

void deinit_gpu() {
	log_info("deinitializing the gpu");

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

#define CYCLES_PER_SECOND 500,000
#define CYCLES_PER_SCREEN (CYCLES_PER_SECOND / (double)60)
#define CYCLES_PER_PIXEL (CYCLES_PER_SCREEN / SCREEN_WIDTH) / (double)2

void render_screen(SDL_Renderer* renderer, cpu_state* cpu_st) {
	SDL_RenderClear(renderer);

	//render pixel buffer here
	printf("%f\n", (((double)CYCLES_PER_SECOND / (double)60) / (double)256) / (double)2);
	printf("%f\n", (((double)500000 / (double)60) / (double)256) / (double)2);

	SDL_RenderPresent(renderer);
}