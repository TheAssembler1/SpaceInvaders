#ifndef GPU_H
#define GPU_H

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

extern SDL_Renderer* renderer;
extern SDL_Window* window;

void init_gpu();
void deinit_gpu();

void render_screen(SDL_Renderer* renderer);

#endif