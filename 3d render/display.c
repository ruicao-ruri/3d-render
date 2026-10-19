#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include"display.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;

int window_width = 800;
int window_height = 600;



bool init_window() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL could not initialize!\n", SDL_GetError());
		return false;
	}

	//
	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);
	window_height = display_mode.h;
	window_width = display_mode.w;

	//create window
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		window_width,
		window_height,
		SDL_WINDOW_BORDERLESS
	);
	if (!window) {
		printf("Window could not be created!\n", SDL_GetError());
		return false;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		printf("Renderer could not be created!\n", SDL_GetError());
		return false;
	}
	//SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	return true;
}
void draw_pixel(int x, int y, uint32_t color) {
	if (x >= 0 && x < window_width && y >= 0 && y < window_height) {
		color_buffer[y * window_width + x] = color;
	}
}

void draw_grid() {
	int grid_size = 10;
	for (int y = 0; y < window_height; y += grid_size) {
		for (int x = 0; x < window_width; x += grid_size) {

			color_buffer[y * window_width + x] = 0xFF333333;

		}
	}
}
void draw_rect(int posx, int posy, int rect_width, int rect_height, uint32_t color) {
	for (int i = 0; i < rect_width; i++) {
		for (int j = 0; j < rect_height; j++) {
			int x = posx + i;
			int y = posy + j;
			//color_buffer[(window_width * y) + x] = color;
			draw_pixel(x, y, color);
		}
	}
}

void render_color_buffer() {
	SDL_UpdateTexture(
		color_buffer_texture,
		NULL,
		color_buffer,
		(int)(window_width * sizeof(uint32_t))
	);
	SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t color) {
	for (int y = 0; y < window_height; y++) {
		for (int x = 0; x < window_width; x++) {
			color_buffer[y * window_width + x] = color;
		}
	}
}

void destroy() {
	free(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
