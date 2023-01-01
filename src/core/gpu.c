#include <headers.h>

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

void render_screen(SDL_Renderer* renderer) {
	long int current_pixel_byte = 0;

	while(current_pixel_byte < VIDEO_BYTES) {
		uint8_t current_byte = read_byte_mem(VIDEO_RAM_START + current_pixel_byte);

		for (int j = 7; j >= 0; j--) {
			int linear_pixel_position = (current_pixel_byte * 8) + j;

			//set render color
			if (BIT_TEST(current_byte, j))
				SDL_SetRenderDrawColor(renderer, ON_PIXEL, 0);
			else
				SDL_SetRenderDrawColor(renderer, OFF_PIXEL, 0);

			int x = linear_pixel_position % SCREEN_WIDTH + 1;
			int y = linear_pixel_position / SCREEN_WIDTH;

			SDL_RenderDrawPoint(renderer, y, SCREEN_WIDTH - x);
		}

		current_pixel_byte++;
	}

	SDL_RenderPresent(renderer);
}