#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "genetic.h"
#include <assert.h>
#include <time.h>
#define WIDTH 780
#define HEIGHT 480
#define BIRD_RADIUS 12
#define NUMBER_OF_POLES 8
typedef struct{
	SDL_FRect bottom_box,
		 top_box; 
	bool visible; 
} pole; 
struct SDL_initialize{
	SDL_Window * main_window; 
	SDL_Renderer * main_renderer;
};
typedef struct{
	double bird_velocity,
		x_position, 
		y_position;
	float fitness;
	bool alive; 
	brain thinker; 
} bird; 
static bool think(bird * birds, pole * obstacles);  
static void normalize_fitness(bird * birds, size_t amount_of_birds);
struct SDL_initialize init(); 
static void free_the_birds(bird * birds); 
inline static void rerender_pole(pole * first,  pole * last, pole * obstacle); 
static bool collision_detection(pole * obstacle, bird * birds, int radius); 
static void starting_poles(pole* result, const int width_pole, const int gap);
inline static pole ** near_poles(pole * obstacle, bird * birds); 
static void close(struct SDL_initialize* init); 
static  bird* create_batch(size_t amount_of_birds);
void gameLoop(struct SDL_initialize* rend_wind, size_t amount);
static void create_bird(SDL_Renderer* render,pole * obstacles ,bird* add, size_t amount_of_birds , int radius);
inline static void jump(bird *birds);
inline static void game_movement(pole * obstacles, double delta_time);
static pole* create_poles(); 
static float distance_to_box(SDL_FRect * box, bird * birds);
static bool birds_dead(bird* birds, size_t amount_of_birds);
static bool outside_bounds(bird * birds); 
static bool detect_one_box(SDL_FRect* obstacle, bird* birds, int radius); 
static bool detect_one(pole * obstacle, bird* birds, int radius);
static void reset_map(pole * obstacles, bird * birds, size_t amount_of_birds);
inline static void gravity(bird * birds, double delta_time ,size_t amount_of_birds); 
inline static void change_y(bird * birds, double delta_time, size_t amount_of_birds); 
inline static void poles(SDL_Renderer* render, pole * obstacles);
static bird* selection(bird * birds,size_t amount_of_birds); 
#endif
