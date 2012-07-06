
#include "Block.h"
#include "Map.h"
#include "Game.h"
int main( int argc, char* args[] )
{
   Game* MyGame = new Game();

   MyGame->GameLoop();

   
    return 0;    
}