#ifndef GPU_H
#define GPU_H

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

SDL_Renderer* renderer;
SDL_Window* window;

void init_gpu();
void deinit_gpu();

void render_screen(SDL_Renderer* renderer);

#endif