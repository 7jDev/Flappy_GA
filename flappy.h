#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#define WIDTH 780
#define HEIGHT 480
struct SDL_initialize{
	SDL_Window * main_window; 
	SDL_Renderer * main_renderer;
};
typedef struct{
	double bird_velocity,
		x_position, 
		y_position;
	bool alive; 
} bird; 
struct SDL_initialize init(); 
static void close(struct SDL_initialize* init); 
bird* create_batch(size_t amount_of_birds);
void gameLoop(struct SDL_initialize* rend_wind);
