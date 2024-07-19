#include "flappy.h"
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
void gameLoop(struct SDL_initialize *rend_wind)
{
SDL_Event e;
bool quit = false; 
time_t before = clock(); 
while(!quit)
{

while(SDL_PollEvent(&e))
{
	if(e.type == SDL_QUIT)
		quit = true;
	else if(e.type == SDL_KEYDOWN) {
		switch(e.key.keysym.sym)
		{

		}
	}
}
SDL_SetRenderDrawColor(rend_wind->main_renderer, 0,104,255,137);
SDL_RenderClear(rend_wind->main_renderer); 
SDL_RenderPresent(rend_wind->main_renderer); 
before = clock(); 

}
close(rend_wind);
return; 
}

