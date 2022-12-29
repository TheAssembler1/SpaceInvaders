#ifndef GPU_H
#define GPU_H

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

#define ON_PIXEL 255, 255, 255
#define OFF_PIXEL 255, 255, 255

//NOTE: The screen is rotated in the cabinet
#define SCREEN_WIDTH (double)256
#define SCREEN_HEIGHT (double)224

extern SDL_Renderer* renderer;
extern SDL_Window* window;

void init_gpu();
void deinit_gpu();

void render_screen(SDL_Renderer* renderer, cpu_state* cpu_st);

#endif