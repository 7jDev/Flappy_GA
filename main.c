#include "flappy.h"
#include "genetic.h"
int main()
{
srand(time(NULL));
rand(); 
struct SDL_initialize stuff= init(); 
gameLoop(&stuff);

}
