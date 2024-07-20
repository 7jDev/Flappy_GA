#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#define WIDTH 780
#define HEIGHT 480
#define BIRD_RADIUS 12
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
static  bird* create_batch(size_t amount_of_birds);
void gameLoop(struct SDL_initialize* rend_wind);
static void create_bird(SDL_Renderer* render, bird* add, size_t amount_of_birds , int radius);
static void render_obstacles(SDL_Renderer* render); 
inline static void jump(); 
