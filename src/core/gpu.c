#include <headers.h>

SDL_Renderer* renderer;
SDL_Window* window;
uint8_t* last_mem_buffer;

void init_gpu() {
	log_info("initializing the gpu");

	window = SDL_CreateWindow(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	SDL_RenderClear(renderer);

	SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

	last_mem_buffer = malloc(VIDEO_BYTES);
	memset(last_mem_buffer, DIFF_PIXEL, VIDEO_BYTES);
}

void deinit_gpu() {
	log_info("deinitializing the gpu");

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	free(last_mem_buffer);
}

void render_screen(SDL_Renderer* renderer) {
	long int current_pixel_byte = 0;
	uint8_t* mem_buffer = get_mem();
	SDL_Color on_pixel;

	while(current_pixel_byte < VIDEO_BYTES) {
		uint8_t current_byte = mem_buffer[VIDEO_RAM_START + current_pixel_byte];

		if (current_byte == last_mem_buffer[current_pixel_byte]) {
			current_pixel_byte++;
			continue;
		}
		else {
			last_mem_buffer[current_pixel_byte] = current_byte;
		}

		for (int j = 7; j >= 0; j--) {
			int linear_pixel_position = (current_pixel_byte * 8) + j;

			int x = linear_pixel_position % SCREEN_WIDTH + 1;
			int y = linear_pixel_position / SCREEN_WIDTH;

			//set render color
			if (BIT_TEST(current_byte, j)){
				if (x <= SPACESHIP_CUTOFF) {
					SDL_SetRenderDrawColor(renderer, SPACESHIP, 0);
				}
				else if (x > SPACESHIP_CUTOFF && x <= SHIELDS_CUTOFF) {
					SDL_SetRenderDrawColor(renderer, SHIELDS, 0);
				}
				else if (x > SHIELDS_CUTOFF && x <= ENEMIES_CUTOFF) {
					SDL_SetRenderDrawColor(renderer, ENEMIES, 0);
				}
				else {
					SDL_SetRenderDrawColor(renderer, TOP_SCREEN, 0);
				}
			}
			else {
				SDL_SetRenderDrawColor(renderer, OFF_PIXEL, 0);
			}

			SDL_RenderDrawPoint(renderer, y, SCREEN_WIDTH - x);;
		}

		current_pixel_byte++;
	}

	SDL_RenderPresent(renderer);
}