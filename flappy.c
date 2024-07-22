#include "flappy.h"
const double thrust = -8.0, gravity_y = -.581;  
struct SDL_initialize init()
{
struct SDL_initialize return_value = {NULL, NULL};
return_value.main_window= SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
if (return_value.main_window== NULL)
	printf("the error was %s", SDL_GetError());  
return_value.main_renderer = SDL_CreateRenderer(return_value.main_window, -1, SDL_RENDERER_ACCELERATED );
if (return_value.main_renderer == NULL)
	printf("the error was %s", SDL_GetError());  
return return_value; 
}
static void close(struct SDL_initialize* init )
{
SDL_DestroyWindow(init->main_window);
SDL_DestroyRenderer(init->main_renderer);
init->main_window = NULL; 
init->main_renderer = NULL; 
SDL_Quit(); 
}
static void create_bird(SDL_Renderer* render, bird* add, size_t amount_of_birds , int radius)
{
	for(size_t i =0; i<amount_of_birds; i++ ){	
	const int diameter = radius*2;
	int x= radius; 
	int y = 0; 
	int tx  =1; 
	int ty =1;
	int error = 1 - radius;
	SDL_SetRenderDrawColor(render, 255, 0 , 0, 255); 
	while(x>=y)
	{
		/*SDL_RenderDrawPoint(render, add->x_position + x,add->y_position + y);	
		SDL_RenderDrawPoint(render, add->x_position + x, add->y_position - y);
		SDL_RenderDrawPoint(render, add->x_position -x, add->y_position -y);
		SDL_RenderDrawPoint(render, add->x_position -x, add->y_position +y );
		SDL_RenderDrawPoint(render, add->x_position + y, add->y_position -x);
		SDL_RenderDrawPoint(render, add->x_position - y, add->y_position +x);
		SDL_RenderDrawPoint(render, add->x_position + y, add->y_position +x);
		SDL_RenderDrawPoint(render, add->x_position - y, add->y_position -x);*/
		SDL_RenderDrawLine(render,add[i].x_position + x, add[i].y_position + y, add[i].x_position + x, add[i].y_position -y); 
		SDL_RenderDrawLine(render,add[i].x_position + y, add[i].y_position + x, add[i].x_position + y, add[i].y_position -x); 
		SDL_RenderDrawLine(render,add[i].x_position -x, add[i].y_position + y, add[i].x_position - x, add[i].y_position -y); 
		SDL_RenderDrawLine(render,add[i].x_position -y, add[i].y_position + x, add[i].x_position - y, add[i].y_position -x); 
		if(error <= 0)
		{
			y++; 
			error += ty; 
			ty += 2; 
		}if(error > 0){
		x--; 
		tx+=2;
		error += (tx - diameter);
		}
	}
	}
	return; 
}
static bird * create_batch(size_t amount_of_birds)
{
	bird * result = calloc( amount_of_birds ,sizeof(bird));
	for(size_t ii=0; ii<amount_of_birds; ii++)
	{
		result[ii].bird_velocity =0; 
		result[ii].x_position = (double)WIDTH/5 ; 
		result[ii].y_position = (double)HEIGHT/2; 
		result[ii].alive = true; 
	}
	return result; 

}
static pole * create_poles()
{
	const int width_pole = 20.0;   
	const int gap = 100; 
	pole * result = calloc(NUMBER_OF_POLES, sizeof(pole));

	for(size_t ii=0; ii< NUMBER_OF_POLES; ++ii)
	{
		//result[ii].bottom_box= {WIDTH/2, 0 , };
	}
	return result;

}
inline static void poles(SDL_Renderer * render)
{
}
inline static void jump(bird * birds){
	birds->bird_velocity = thrust;
}
inline static void gravity(bird * birds, double delta_time ,size_t amount_of_birds)
{
	for(size_t i=0; i< amount_of_birds; ++i)
	{
		birds[i].bird_velocity -= gravity_y * delta_time;
	} 	

}
inline static void change_y(bird * birds, double delta_time ,size_t amount_of_birds)
{
	for(size_t i=0; i< amount_of_birds; ++i){
		birds[i].y_position += birds[i].bird_velocity *delta_time; 
	} 	
}
void gameLoop(struct SDL_initialize *rend_wind)
{
bird * birds; 
const size_t amount_of_birds = 5;
SDL_Event e;
pole example; 
example.bottom_box.w = 20 ;
example.bottom_box.h = -50 ;
example.bottom_box.x = WIDTH/2 ;
example.bottom_box.y = HEIGHT;
bool quit = false; 
time_t before = clock(); 
birds = create_batch(amount_of_birds);
while(!quit)
{
double delta_time = (double)(clock() - before)/1000.0;
if (delta_time > 0.1)
	delta_time = 0.1; 
else if (delta_time < 0.065)
	delta_time = 0.065;
while(SDL_PollEvent(&e))
{
	if(e.type == SDL_QUIT)
		quit = true;
	else if(e.type == SDL_KEYDOWN) {
		switch(e.key.keysym.sym)
		{
			case SDLK_SPACE:
			jump(birds); 	
		}
	}
}
change_y(birds, delta_time, amount_of_birds);
gravity(birds, delta_time, amount_of_birds);
SDL_SetRenderDrawColor(rend_wind->main_renderer, 0,104,255,137);
SDL_RenderClear(rend_wind->main_renderer); 
SDL_SetRenderDrawColor(rend_wind->main_renderer, 0,0,0,0);
SDL_RenderFillRect(rend_wind->main_renderer, &example.bottom_box);
SDL_RenderDrawRect(rend_wind->main_renderer,&example.bottom_box); 
create_bird(rend_wind->main_renderer, birds, amount_of_birds, BIRD_RADIUS); 
SDL_RenderPresent(rend_wind->main_renderer); 
before = clock(); 
}
free(birds);  
close(rend_wind);
return; 
}
