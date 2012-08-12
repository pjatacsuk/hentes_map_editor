#ifndef INC_PLAYER_H
#define INC_PLAYER_H


#include "TextureManager.h"
#include "Map.h"
#include "Entity.h"
#include "resource.h"
using namespace resource;

class Player{
private:
	sf::Vector2<float>		_coord;							//coordin�t�ja
	int						_movement_type;					//ez m�g csak anim�ci�hoz kell
	sf::Vector2<float>		_speed_cap;
	int						_speed_increase;
	sf::Vector2<float>		_size;
	bool					_jumping;
	
public:
	sf::Vector2<float>		  _speed;
	Player(sf::Vector2<float> coord,sf::Vector2<float> speed);
	~Player();
	void			Render(sf::RenderWindow* target,TextureManager* textureManager,sf::Vector2<float>& offSet);
	void			UpdateKey(sf::Event& my_event,sf::Vector2<float>& offSet,Map* map);
	void			UpdatePosition();
	void			UpdateVelocity(Map* map);
	void			Jump();
	void			MovePlayer(int direction,sf::Vector2<float>& offSet,Map* map);
	bool			CheckCollosion(int direction,Map* map);
	void			CollosionLogic(Map* map);
	
	

};
#endif