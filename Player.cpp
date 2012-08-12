#include "Player.h"
#include "resource.h"
Player::Player(sf::Vector2<float> coord, sf::Vector2<float> speed):
_speed(speed),
_coord(coord),
_speed_cap(15,15),
_speed_increase(5),
_movement_type(2),
_jumping(false),
_size(sf::Vector2<float>(resource::consts::BLOCK_SIZE,resource::consts::BLOCK_SIZE))

{

}

Player::~Player() {

}

void Player::Render(sf::RenderWindow* target,TextureManager* textureManager,sf::Vector2<float>& offSet) {
	sf::Sprite sprite(textureManager->operator[](_movement_type),_coord + offSet);
	target->Draw(sprite);
}

bool Player::CheckCollosion(int direction,Map* map) {
	int ray;
	switch(direction) {
	case UP:
		ray = _coord.y ;
		return	map->GetColBox(sf::Vector2<float>(_coord.x/resource::consts::BLOCK_SIZE,ray/resource::consts::BLOCK_SIZE));
		break;
	case DOWN:
		ray = _coord.y + _size.y + _speed.y  ;
		return	map->GetColBox(sf::Vector2<float>(_coord.x/resource::consts::BLOCK_SIZE,ray/resource::consts::BLOCK_SIZE));
		break;

	case LEFT:
		ray = _coord.x  ;
		return	map->GetColBox(sf::Vector2<float>(ray/resource::consts::BLOCK_SIZE,_coord.y/resource::consts::BLOCK_SIZE));
		break;
	case RIGHT:
		ray = _coord.x + _size.x ;
		return	map->GetColBox(sf::Vector2<float>(ray/resource::consts::BLOCK_SIZE,_coord.y/resource::consts::BLOCK_SIZE));
		break;
	}
	return false;
}
void Player::MovePlayer(int direction,sf::Vector2<float>& offSet,Map* map) {
	


	switch(direction) {

	case UP:
		_speed.y = -10  ;
		if(_coord.y - offSet.y  - _speed.y < 0	+	resource::consts::SCREEN_EDGE) {
			offSet.y  -= _speed.y;
		}
		
		break;
	case DOWN:
		
		if(_coord.y - offSet.y + _speed.y >  resource::consts::SCREEN_HEIGHT  - resource::consts::SCREEN_EDGE) {
			offSet.y += _speed.y;
		}
		
		break;
	case LEFT:
		if(_speed.x > 0 ) _speed.x = 2 ;		//csúszás csökkentése reakció során
		if(_speed.x - _speed_increase >= -1* _speed_cap.x) {
			_speed.x -= _speed_increase;
		}
		if(_coord.x - offSet.x - _speed_cap.x < 0	+ resource::consts::SCREEN_EDGE) {
			offSet.x -= _speed_cap.x;
		}
	
		break;
	case RIGHT:
		if(_speed.x < 0) _speed.x = 2 ;	//csúszás csökkentése reakció után
		if(_speed.x + _speed_increase <= _speed_cap.x) {
			_speed.x += _speed_increase;

		}
		
		if(_coord.x - offSet.x + _speed_cap.x > resource::consts::SCREEN_WIDTH - resource::consts::SCREEN_EDGE) {
			offSet.x += _speed_cap.x;
		}
		
		break;

	}
	

	
	
}
void Player::UpdateKey(sf::Event& my_event,sf::Vector2<float>& offSet,Map* map) {
	switch(my_event.Type) {
	case sf::Event::KeyPressed:
		switch(my_event.Key.Code) {
				case sf::Key::W:
					
					MovePlayer(UP,offSet,map);
					_jumping = true;
					break;

				case sf::Key::A:
					MovePlayer(LEFT,offSet,map);
					break;
				case sf::Key::S:
					MovePlayer(DOWN,offSet,map);
					break;
				case sf::Key::D:
					MovePlayer(RIGHT,offSet,map);
					break;

		}
		break;
	}
	
}

void Player::UpdateVelocity(Map* map) {
	
	
	if(abs(_speed.x) - 1 >= 0) {
		if(_speed.x > 0 ) {
			_speed.x -= 1;
		} else {
			_speed.x += 1;
		}
	}
	
		
	if(CheckCollosion(DOWN,map)==false) {
			_speed.y += 1;
	}
	
}
void Player::UpdatePosition() {


	_coord.x +=  _speed.x;
	_coord.y +=  _speed.y;

	
}

void Player::CollosionLogic(Map* map) {
	bool is_coll = false;
	if(_speed.y != 0) { 
		if(CheckCollosion(DOWN,map) == true) {
			
			
			_coord.y -= 1;
			_speed.y = 0;
		}
		if(CheckCollosion(UP,map) == true) {
			_speed.y = 0;
			_coord.y += 1;
			
		}
		
		
	}
	if(_speed.x != 0) {
			if(CheckCollosion(LEFT,map) == true) {  
					_coord.x += 1 ;
					_speed.x = 0;
			}  
			if(CheckCollosion(RIGHT,map) == true) {
					_coord.x -= 1 ;
					_speed.x =0;
			}
		}
}

		
	
