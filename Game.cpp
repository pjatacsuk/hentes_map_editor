#include "Game.h"
#include "Block.h"
#include "resource.h"
#include "Editor.h"

Game::Game():
running(true),
game_status(MENU),
App(NULL),
map(NULL) 
{
	Init_Game();
	
	
}
Game::~Game() {
	App->Close();
	delete map;
	delete entityManager;
	delete textureManager;
}

void Game::Init_Game() {
	App = new sf::RenderWindow(sf::VideoMode(resource::consts::SCREEN_WIDTH,
								resource::consts::SCREEN_HEIGHT),"SFML");
	
	entityManager = new EntityManager();
	textureManager = new TextureManager("./textures.txt");
/*	textureManager->Add("./data/images/block_normal.png");
	textureManager->Add("./data/images/player.png");
	textureManager->Add("./data/images/block_grass.png");
	textureManager->Add("./data/images/block_water.png");
	textureManager->Add("./data/images/block_random.png");
	textureManager->Add("./data/images/block_random2.png");
	textureManager->Add("./data/images/block_lava.png");
	textureManager->Add("./data/images/block_random3.png");
	textureManager->Add("./data/images/block_random2.png");
	//textureManager->Add("./data/images/block_lava.png");
	textureManager->Add("./data/images/block_random3.png");
	textureManager->Add("./data/images/proba.png"); */
	
}

void Game::GameMenu() {
	sf::Event my_event;
	
	while(App->GetEvent(my_event)) {
		switch(my_event.Type) {
		case sf::Event::KeyPressed: 
			switch(my_event.Key.Code) {
			case sf::Key::Num1:
							game_status = GAMEPLAY;
						break;
			case sf::Key::Num2:
							game_status = EDITOR;
							break;
				}
			break;
		}
	}
	App->Display();


}
void Game::GameLoop() {
	while(running) {
		switch(game_status) {
		case MENU:
			GameMenu();
			break;
		case EDITOR:
			GameEditor();
			break;
		
		case GAMEPLAY:
			GamePlay();
			break;
		case MAPCHOOSE:
			MapChoose();
			break;
		}
	}
}



void Game::Free_Game() {
}

void Game::GamePlay() {
/*	EntityManager* eM = new EntityManager();
	Block* blck = new Block(1,Vector<int>(3,2));
	Block* blck2 = new Block(1,Vector<int>(3,2));
	Block* blck3 = new Block(1,Vector<int>(4,2));
	Block A = Block();
	Block B = Block();
	
	if((*blck) < (*blck3)) {
		return;
	}*/
}

void Game::MapChoose() {

}

void Game::GameEditor() {
	Editor* editor = new Editor("map1.txt");
	editor->Loop(App,textureManager);
	game_status = MENU;
}