#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>

bool isrunning = false;

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
	renderer = SDL_CreateRenderer(window, -1,0);
	if (!renderer) {
		printf("Renderer could not be created!\n", SDL_GetError());
		return false;
	}
	//SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	return true;
}

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
void draw_grid() {
	int grid_size = 10;
	for (int y = 0; y < window_height; y+=grid_size) {
		for (int x = 0; x < window_width; x+=grid_size) {
			
				color_buffer[y * window_width + x] = 0xFF333333;
			
		}
	}
}
void draw_rect(int posx,int posy,int rect_width,int rect_height,uint32_t color) {
	for (int y = posy; y < posy + rect_height;y++) {
		for (int x = posx;x < posx + rect_width;x++) {
			color_buffer[y * window_width + x] = color;
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

void render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	draw_grid();
	draw_rect(1000,500,192,108,0xFFFF0000);

	render_color_buffer();
	clear_color_buffer(0xFF000000);
	SDL_RenderPresent(renderer);                                                                                                                                                                                                                                                                                                                                                                                           SDL_RenderPresent(renderer);
}

void destroy() {
	free(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
int main(int argc, char* argv[]) {
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