#ifndef DISPLAY_H
#define DISPLAY_H
#include <SDL.h>
#include <stdint.h>
#include<stdbool.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern uint32_t* color_buffer;
extern SDL_Texture* color_buffer_texture;

extern int window_width;
extern int window_height;

bool init_window();

void draw_grid();
void draw_rect(int posx, int posy, int rect_width, int rect_height, uint32_t color);
void draw_pixel(int x, int y, uint32_t color);

void render_color_buffer();
void clear_color_buffer(uint32_t color);
void destroy();


#endif 