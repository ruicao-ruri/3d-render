#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include "display.h"


bool isrunning = false;



void setup() {
	color_buffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);

	color_buffer_texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		window_width,
		window_height
	);
}

void process_input() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isrunning = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				isrunning = false;
			}
			break;
	}
}
void update() {
	
}
void render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	draw_grid();
	draw_rect(1000,500,192,108,0xFFFF0000);

	render_color_buffer();
	clear_color_buffer(0xFF000000);
	SDL_RenderPresent(renderer);                                                                                                                                                                                                                                                                                                                                                                                           SDL_RenderPresent(renderer);
}

int main() {
	isrunning = init_window();
	setup();
	while (isrunning) {
		process_input();
		update();
		render();
		printf("Running...\n");
	}
	destroy();
	return 0;
}