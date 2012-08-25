#include "Game.h"
#include "Block.h"
#include "resource.h"
#include "Editor.h"
#include "Menu.h"
Game::Game(QWidget* Parent, const QPoint& Position, const QSize& Size) :
QSFMLCanvas(Parent, Position, Size),
running(true),
game_status(MENU),
App(NULL),
map(NULL),
textureManager(NULL),
editor(NULL)
{
	
	menu = new Menu(this);
	
	
}
Game::~Game() {
	App->Close();
	delete map;
	delete textureManager;
	delete menu;
	delete editor;
}

void Game::OnInit() {
	/*App = new sf::RenderWindow(sf::VideoMode(resource::consts::SCREEN_WIDTH,
								resource::consts::SCREEN_HEIGHT),"SFML");
	*/
	textureManager = new TextureManager("./textures.txt");
}

void Game::GameMenu() {
	map_path = menu->Loop();
	if(map_path != "")	game_status = EDITOR;
	
	


}
void Game::OnUpdate() {
//	while(running) {
	Clear();
		switch(game_status) {
		case MENU:
			GameMenu();
			break;
		case EDITOR:
			GameEditor();
			break;
		}
//	}
}





void Game::GameEditor() {
	if(editor == NULL) {
		editor = new Editor(map_path,textureManager,this);
	}
	if(map_path != editor->GetCurrentMap()) {
		delete editor;
		editor = new Editor(map_path,textureManager,this);
	}
	
	if(editor->Loop() == false)	{
		game_status = MENU;
		map_path = "";
	}
	
}