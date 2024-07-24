#include "flappy.h"
#include "genetic.h"
int main()
{
srand(time(NULL));
rand(); 
float x[5] = {0.1, 0.2, 0.3 , 0.4, 0.5};
neuron first = initialize_neuron(5); 
float answer = compute_neuron(&first, x, SIGMOID);
printf("the answer is %f", answer); 
struct SDL_initialize stuff= init(); 
gameLoop(&stuff);

}
