#ifndef INC_GAMEPLAY_H
#define INC_GAMEPLAY_H
#include "Player.h"
#include "TextManager.h"
#include "TextureManager.h"
#include "Map.h"
#include "resource.h"
class GamePlay{
private:
	Map*					_map;
	bool					_running;
	sf::Vector2<float>		_offSet;
	TextManager*			_textManager;
	Player*					_player;
public:
	GamePlay(Map* map,sf::Vector2<float> offSet);
	GamePlay(Map* map,sf::Vector2<float> offSet,sf::Vector2<float> player_coord);
	~GamePlay();
	
	void			Render(sf::RenderWindow* target,TextureManager* textureManager);
	void			Loop(sf::RenderWindow* target,TextureManager* textureManager);
};

#endif