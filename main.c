#include "flappy.h"
#include "genetic.h"
int main(int argc, char * argv[])
{
srand(time(NULL));
rand(); 
assert(argc == 2);
int birds_amount = atoi(argv[1]);
struct SDL_initialize stuff= init(); 
gameLoop(&stuff, birds_amount);

}
