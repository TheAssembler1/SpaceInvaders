#ifndef GPU_H
#define GPU_H

#define DIFF_PIXEL 1
#define OFF_PIXEL 0, 0, 0

#define SPACESHIP 66, 233, 244
#define SHIELDS 98, 222, 109
#define ENEMIES 248, 59, 58
#define TOP_SCREEN 219, 85, 221

#define BACKGROUND_COLOR 0, 0, 0

//NOTE: The screen is rotated in the cabinet
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 224

#define WINDOW_WIDTH SCREEN_HEIGHT
#define WINDOW_HEIGHT SCREEN_WIDTH


#define SPACESHIP_CUTOFF 40
#define SHIELDS_CUTOFF 64
#define ENEMIES_CUTOFF 224

#define CYCLES_PER_SCREEN (CYCLES_PER_SECOND / (double)60)
#define CYCLES_PER_HALF_WIDTH_OF_ROW (CYCLES_PER_SCREEN / SCREEN_WIDTH) / (double)2

#define VIDEO_RAM_START 0x2400
#define VIDEO_RAM_END 0x3FFF

#define VIDEO_BYTES 7168

#define HALFWAY_INTERRUPT 0xCF
#define FULL_INTERRUPT 0xD7

extern SDL_Renderer* renderer;
extern SDL_Window* window;

void init_gpu();
void deinit_gpu();

void render_screen(SDL_Renderer* renderer);

#endif