#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include "display.h"
#include "vector.h"
//#include "vector.c"

#define M_POINTS  9*9*9
Vector3_t cube_points[M_POINTS];
Vector2_t projected_points[M_POINTS];
float fov_factor = 128;

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
	//start loading my vectors
	int point_count = 0;
	//From -1 to 1
	for (float x = -1;x <= 1; x += 0.25) {
		for (float y = -1;y <= 1;y += 0.25) {
			for (float z = -1;z <= 1; z += 0.25) { 
				Vector3_t newpoint = { .x = x,.y = y,.z = z };
				cube_points[point_count++] = newpoint;

			}
		}
	}

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
// Function to project a 3D point onto a 2D plane
Vector2_t project(Vector3_t point) {
	Vector2_t projected_point;
	projected_point.x =fov_factor* (point.x) ;
	projected_point.y =fov_factor* (point.y );
	return projected_point;
}

void update() {
	for (int i = 0; i < M_POINTS; i++) {
		Vector3_t point = cube_points[i];

		// Project the current point
		Vector2_t projected_point = project(point);

		//save
		projected_points[i] = projected_point;

		
	}
}
void render() {

	draw_grid();
	// Draw the projected points
	for (int i = 0; i < M_POINTS; i++) {
		Vector2_t projected_point = projected_points[i];
		draw_rect(
			projected_point.x+(window_width/2),
			projected_point.y+(window_height/2),
			4, 4, 0xFFFFFF00);
		
	}

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