#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>

bool isrunning = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


bool init_window() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL could not initialize!\n", SDL_GetError());
		return false;
	}
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 
		800, 
		600,
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

	return true;
}

void setup() {
	
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
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);

	                                                                                                                                                                                                                                                                                                                                                                                               SDL_RenderPresent(renderer);
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
	return 0;
}