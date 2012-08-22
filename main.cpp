
#include "Block.h"
#include "Map.h"
#include "Game.h"



int main( int argc, char* args[] )
{
   Game* MyGame = new Game();
 //  resource::consts::myTextureManager = new TextureManager("./textures.txt");
   MyGame->GameLoop();

//   delete myTextureManager;
    return 0;    
}