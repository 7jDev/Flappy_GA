#include "flappy.h"
const double thrust = -8.0, gravity_y = -.375;  
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
inline static pole ** near_poles(pole * obstacle, bird * birds)
{
	pole ** result = calloc(2, sizeof(pole *));
	pole * close = obstacle; 
	pole * close_two = obstacle +1; 
	float x_pos = birds->x_position;
	for(size_t i=0; i< NUMBER_OF_POLES; ++i)
	{
 		float first = (close->bottom_box.x - x_pos);
		first = first <0.0? -first: first; 
 		float second= (close_two->bottom_box.x - x_pos);
		second= second<0.0? -second: second; 
 		float compare= (obstacle[i].bottom_box.x - x_pos);
		compare= compare<0.0? -compare: compare; 
		if(first > compare)
		{
		close = &obstacle[i]; 	
		}
		else if (second > compare )
		{
		close_two = &obstacle[i];
		}
	}
	result[0] = close; 
	result[1] = close_two; 
	return result;
}  
static bool collision_detection(pole * obstacle, bird * birds, int radius)
{
	if(!birds->alive)
		return false; 
	pole ** result = near_poles(obstacle, birds);
	birds->alive = !detect_one(result[0], birds,radius);
	free(result);
	return birds->alive; 

}
static bool detect_one_box(SDL_FRect * obstacle, bird * birds, int radius)
{
	bool first = false;
	bool second = false; 
	if((obstacle->x +obstacle-> w) >= birds->x_position && obstacle->x <= birds->x_position) first = true; 
	if((obstacle->y +obstacle-> h) >= birds->y_position && obstacle->y <= birds->y_position) second= true; 
	if((obstacle->y +obstacle-> h) <= birds->y_position&& obstacle->y >= birds->y_position) second= true; 
	return first && second; 
}
static bool detect_one(pole * obstacle, bird * birds, int radius)
{
	return detect_one_box(&obstacle->bottom_box, birds,radius) || detect_one_box(&obstacle->top_box, birds, radius);
}
static bool outside_bounds(bird *birds)
{
	if(!birds->alive)
		return false;
	if(birds->y_position >= HEIGHT || birds->y_position <= 0)
		birds->alive = false;
	return true;
} 
static bool birds_dead(bird* birds, size_t amount_of_birds)
{
	for(size_t i=0; i< amount_of_birds ; ++i)
		if(birds[i].alive)
			return false;
	return true;
}
static void normalize_fitness(bird * birds,size_t amount_of_birds)
{
	float sum = 0.0;
	for(size_t i=0; i<amount_of_birds; ++i){
		sum +=birds[i].fitness; 
	}
	for(size_t i=0; i<amount_of_birds; ++i){
		birds[i].fitness = birds[i].fitness/ sum;
	}
}
static bird * selection(bird * birds, size_t amount_of_birds)
{
	size_t index = 0;
	float start = (float)rand() / RAND_MAX; 
	while(start > 0)
	{
	if(index >= amount_of_birds)
		index--;
	start = start - birds[index].fitness; 
	index++;
	}
	index--; 
	return &birds[index];
} 
static void reset_map(pole * obstacles, bird * birds, size_t amount_of_birds)
{
	const int width_pole = 30.0;   
	const int gap = 175;
	starting_poles(obstacles,width_pole, gap);
	normalize_fitness(birds, amount_of_birds);
	bird temp[amount_of_birds];
	memcpy(temp, birds, amount_of_birds * sizeof(bird));
	for(size_t i=0; i< amount_of_birds; ++i)
		birds[i].thinker = crossover(&selection(temp, amount_of_birds)->thinker , &selection(temp, amount_of_birds)->thinker);
	for(size_t i=0; i < amount_of_birds; ++i )
	{

		birds[i].bird_velocity =0; 
		birds[i].x_position = (double)WIDTH/5 ; 
birds[i].y_position = (double)HEIGHT/2; 
		birds[i].fitness = 0; 
		birds[i].alive = true; 
	}
}
static void create_bird(SDL_Renderer* render, pole* obstacles ,bird* add, size_t amount_of_birds , int radius)
{
	if(birds_dead(add,amount_of_birds))
	{
		reset_map(obstacles, add, amount_of_birds); 
		return;
	}
	for(size_t i =0; i<amount_of_birds; i++ ){

	if(add[i].alive){
	outside_bounds(&add[i]);
	collision_detection(obstacles, &add[i],radius);
//	think(&add[i], obstacles);
	if(think(&add[i], obstacles))
		jump(&add[i]);
	add[i].fitness += 1; 
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
	}
	return; 
}
static float distance_to_box(SDL_FRect * box, bird * birds)
{
	float y_temp; 
	if((int)box->y == HEIGHT){
		y_temp = HEIGHT + box->h;
	}	
	else
		y_temp = box->h;
	float x_temp = box->x - birds->x_position; 	
	y_temp =y_temp - birds->y_position;  
	float result= sqrt((x_temp * x_temp) +(y_temp * y_temp));
	return result; 
}
static bool think(bird * birds, pole * obstacles)
{
	bool return_val; 
	pole ** result = near_poles(obstacles, birds);
	pole * pole_to_search = (result[0]->bottom_box.x > result[1]->bottom_box.x) ?
				 result[0]:result[1];
	float input[birds->thinker.num_inputs];
	input[0] = (result[0]->top_box.x -birds->x_position) / WIDTH; 
	input[1] = birds->y_position/ HEIGHT; 
	input[2] = birds->bird_velocity / 8.0; 
	input[3] = distance_to_box(&result[0]->top_box, birds) / 200;//top 
	input[4] = distance_to_box(&result[0]->bottom_box, birds) /200; //bottom
	float *temp = compute_brain(&birds->thinker, input); 
	//if(*temp> 0.5)
		//printf("the value is %f", *temp);
	return_val = (*temp < 0.5) ? true : false; 	
	free(result);
	return return_val; 
}
static bird * create_batch(size_t amount_of_birds)
{
	//inputs to brain = velocity, xpos, ypos, distance to top, distance to bottom
	size_t *neurons_per = calloc(3, sizeof(size_t));
	neurons_per[0]= 5; neurons_per[1]= 3; neurons_per[2]= 1; 
	activation*func_per= calloc(3, sizeof(activation));
	func_per[0]= RELU; func_per[1]= RELU; func_per[2]= SIGMOID; 
	bird * result = calloc( amount_of_birds ,sizeof(bird));
	for(size_t ii=0; ii<amount_of_birds; ii++)
	{
		result[ii].bird_velocity =0; 
		result[ii].x_position = (double)WIDTH/5 ; 
		result[ii].y_position = (double)HEIGHT/2; 
		result[ii].fitness = 0; 
		result[ii].alive = true; 
		result[ii].thinker = initialize_brain(3,5,neurons_per, func_per);
	}
	return result; 

}
static void starting_poles(pole *result, const int width_pole, const int gap)
{
	int next_pole = 0; 
	for(size_t ii=0; ii< NUMBER_OF_POLES; ++ii, next_pole += 200)
	{
		int randomness = rand() % 255; 
		SDL_FRect temp_bottom={
			(float)WIDTH/2 + next_pole,
			HEIGHT, 
			width_pole, 
			-(HEIGHT - (randomness+ gap))	
			};
		SDL_FRect temp_top={
			(float)WIDTH/2  + next_pole, 
			0, 
			width_pole,
			randomness,
		};
		result[ii].bottom_box= temp_bottom; 
		result[ii].top_box = temp_top; 
		result[ii].visible = true; 
	}

}
static pole * create_poles()
{
	const int width_pole = 30.0;   
	const int gap = 175;
	pole * result = calloc(NUMBER_OF_POLES, sizeof(pole));
	starting_poles(result, width_pole, gap);
	return result;
}
inline static void game_movement(pole * obstacles, double delta_time)
{
for(size_t i=0; i< NUMBER_OF_POLES; ++i)
{
	obstacles[i].bottom_box.x -= 2.5 * delta_time; 
	obstacles[i].top_box.x -= 2.5* delta_time; 
}
} 
inline static void rerender_pole(pole * first , pole * last, pole * obstacle)
{
	const int width_pole = 30.0;   
	const int gap = 150;
	const int next_pole = 200;
	int randomness = rand() % 255; 
		SDL_FRect temp_bottom={
			last->bottom_box.x + next_pole,
			HEIGHT, 
			width_pole, 
			-(HEIGHT - (randomness+ gap))	
			};
		SDL_FRect temp_top={
			last->top_box.x + next_pole, 
			0, 
			width_pole,
			randomness,
		};
	obstacle->top_box = temp_top; 
	obstacle->bottom_box = temp_bottom;
	pole  temp = *last; 
	*last = *obstacle; 
	*obstacle = temp;  
}
inline static void poles(SDL_Renderer * render, pole* obstacles)
{
	SDL_SetRenderDrawColor(render, 0,0,0,0); 
	for(size_t i=0; i< NUMBER_OF_POLES; ++i)
	{
		if(obstacles[i].bottom_box.x < 0)
		{
		obstacles[i].visible =false; 
		rerender_pole(&obstacles[0] ,&obstacles[NUMBER_OF_POLES -1] ,&obstacles[i]);
		}
		SDL_RenderFillRectF(render, &obstacles[i].bottom_box); 	
		SDL_RenderFillRectF(render, &obstacles[i].top_box); 	
		SDL_RenderDrawRectF(render, &obstacles[i].bottom_box); 	
		SDL_RenderDrawRectF(render, &obstacles[i].top_box); 	
	}
	return; 
}
inline static void jump(bird * birds){
	birds->bird_velocity = thrust;
}
inline static void gravity(bird * birds, double delta_time ,size_t amount_of_birds)
{
	for(size_t i=0; i< amount_of_birds; ++i)
	{
		if(!(birds[i].bird_velocity > 8.0))
			birds[i].bird_velocity -= gravity_y * delta_time;
	} 	

}
inline static void change_y(bird * birds, double delta_time ,size_t amount_of_birds)
{
	for(size_t i=0; i< amount_of_birds; ++i)
		birds[i].y_position += birds[i].bird_velocity *delta_time; 
	
}
void gameLoop(struct SDL_initialize *rend_wind, size_t amount)
{
bird * birds; 
pole* obstacles;
const size_t amount_of_birds = amount;
SDL_Event e;
bool quit = false; 
time_t before = clock(); 
birds = create_batch(amount_of_birds);
obstacles = create_poles(); 
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
game_movement(obstacles, delta_time); 
poles(rend_wind->main_renderer, obstacles);
create_bird(rend_wind->main_renderer, obstacles,  birds, amount_of_birds, BIRD_RADIUS); 
SDL_RenderPresent(rend_wind->main_renderer); 
before = clock(); 
}
free(birds);  
close(rend_wind);
return; 
}
