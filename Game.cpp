#include "Game.h"
#include "Block.h"
#include "resource.h"
#include "Editor.h"
#include "Menu.h"
Game::Game():
running(true),
game_status(MENU),
App(NULL),
map(NULL),
textureManager(NULL)
{
	Init_Game();
	
	
}
Game::~Game() {
	App->Close();
	delete map;
	delete textureManager;
}

void Game::Init_Game() {
	App = new sf::RenderWindow(sf::VideoMode(resource::consts::SCREEN_WIDTH,
								resource::consts::SCREEN_HEIGHT),"SFML");
	
	textureManager = new TextureManager("./textures.txt");
}

void Game::GameMenu() {
	Menu* menu = new Menu(App);
	map_path = menu->Loop();
	game_status = EDITOR;
	delete menu;
	


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
		}
	}
}





void Game::GameEditor() {
	Editor* editor = new Editor(map_path,textureManager,App);
	editor->Loop();
	game_status = MENU;
	delete editor;
}