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
	long unsigned int fitness;
	bool alive; 
	brain thinker; 
} bird; 
struct SDL_initialize init(); 
inline static void rerender_pole(pole * first,  pole * last, pole * obstacle); 
inline static void collision_detection(pole * obstacle, bird * birds); 
inline static pole ** near_poles(pole * obstacle, bird * birds, pole *result[2]); 
static void close(struct SDL_initialize* init); 
static  bird* create_batch(size_t amount_of_birds);
void gameLoop(struct SDL_initialize* rend_wind);
static void create_bird(SDL_Renderer* render,pole * obstacles ,bird* add, size_t amount_of_birds , int radius);
inline static void jump(bird *birds);
inline static void game_movement(pole * obstacles, double delta_time);
static pole* create_poles(); 
inline static void gravity(bird * birds, double delta_time ,size_t amount_of_birds); 
inline static void change_y(bird * birds, double delta_time, size_t amount_of_birds); 
inline static void poles(SDL_Renderer* render, pole * obstacles);
#endif
