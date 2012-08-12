#include "GamePlay.h"
#include "MyTimer.hpp"
#include <sstream>
GamePlay::GamePlay(Map* map,sf::Vector2<float> offSet,sf::Vector2<float> player_coord):
_map(map),
_offSet(offSet){
	_player = new Player(player_coord,sf::Vector2<float>(0,0));
	_textManager = new TextManager("./data/fonts/Calibri.ttf");
	_map->GenerateCollBoxes();
}

GamePlay::GamePlay(Map* map,sf::Vector2<float> offSet):
_map(map),
_offSet(offSet){
	_player = new Player(sf::Vector2<float>(30,30),sf::Vector2<float>(0,0));
	_textManager = new TextManager("./data/fonts/Calibri.ttf");
	_map->GenerateCollBoxes();
}


GamePlay::~GamePlay() {
	delete _player;
	delete _textManager;
	delete _map;
}

void GamePlay::Render(sf::RenderWindow* target, TextureManager* textureManager) {
	sf::Image image(resource::consts::SCREEN_WIDTH,
					resource::consts::SCREEN_HEIGHT,
					sf::Color(48,124,211));
	sf::Sprite sprite(image,sf::Vector2<float>(0,0));
	target->Draw(sprite);
	_map->Render(target,textureManager,_offSet);
	_player->Render(target,textureManager,_offSet);
	_textManager->DisplayText(target);
	
}

void GamePlay::Loop(sf::RenderWindow* target,TextureManager* textureManager) {
	sf::Event MyEvent;
	MyTimer fps = MyTimer(1000/resource::consts::FPS);
	int frame = 0;
	fps.StartTimer();
	int key_down = 0;
	while(_running) {
		
		
		
		
		if(frame % resource::consts::FPS == 0) {
			while(target->GetEvent(MyEvent)) {
					_player->UpdateKey(MyEvent,_offSet,_map);
					switch(MyEvent.Type) {
					case sf::Event::KeyPressed:
						key_down = 1;
						switch(MyEvent.Key.Code) {
						case sf::Key::Escape:
							_running = false;
							break;
						}
						break;
					case sf::Event::KeyReleased:
						key_down = false;
						break;
					}
					
				}
			
			if(!key_down) {
			_player->UpdateVelocity(_map);
			}
			target->Clear();
			_player->UpdatePosition();
			_player->CollosionLogic(_map);
			Render(target,textureManager);

			}
		
		target->Display();
		frame++;
		if( fps.GetTicks() < 1000 / resource::consts::FPS ) 
        {
		
            //Sleep the remaining frame time
		//	SDL_Delay( ( 1000 / resource::consts::FPS ) - fps.GetTicks() );
        }

	}
}