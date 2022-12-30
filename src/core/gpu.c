#include <headers.h>

SDL_Renderer* renderer;
SDL_Window* window;
long int current_pixel_byte;

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

#define HALFWAY_INTERRUPT 0xCF
#define FULL_INTERRUPT 0xD7

void render_screen(SDL_Renderer* renderer, cpu_state* cpu_st) {
	while(cpu_st->cycles >= CYCLES_PER_HALF_WIDTH_OF_ROW ) {
		cpu_st->cycles -= CYCLES_PER_HALF_WIDTH_OF_ROW;

		//render 128 pixels which is 16 bytes
		for (int i = current_pixel_byte; i < current_pixel_byte + 16; i++) {
			uint8_t current_byte = read_byte_mem(VIDEO_RAM_START + i);

			for (int j = 7; j >= 0; j--) {
				int linear_pixel_position = (i * 8) + j;

				//set render color
				if (BIT_TEST(current_byte, j))
					SDL_SetRenderDrawColor(renderer, ON_PIXEL, 0);
				else
					SDL_SetRenderDrawColor(renderer, OFF_PIXEL, 0);

				int x = linear_pixel_position % SCREEN_WIDTH + 1;
				int y = linear_pixel_position / SCREEN_WIDTH;

				//log_log("%d = (%d, %d)", linear_pixel_position, x, y);

				SDL_RenderDrawPoint(renderer, y, SCREEN_WIDTH - x);
			}
		}

		current_pixel_byte += 16;

		if (current_pixel_byte == VIDEO_BYTES / 2) {
			execute_interrupt(HALFWAY_INTERRUPT);
		}else if (current_pixel_byte >= VIDEO_BYTES) {
			current_pixel_byte = 0;
			execute_interrupt(FULL_INTERRUPT);
		}
	}

	SDL_RenderPresent(renderer);
}