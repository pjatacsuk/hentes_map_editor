#include "Entity.h"
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include "TextureManager.h"
#ifndef INC_BLOCK_H
#define INC_BLOCK_H

class Block : public Entity {
private:
  
  sf::Vector2<float>	_coord;
  int					_type;
public:
							Block(int type,sf::Vector2<float> coord); 
							Block();
//  virtual					~Block();

  virtual	void			Render(sf::RenderWindow* app,TextureManager* textureManager,sf::Vector2<float> offSet);
  virtual	void			Update();

  virtual	std::string		Serialize();
  virtual	void			deSerialize(std::string line);

			bool			operator<(const Entity* entity);
			bool			operator==(const Entity* entity);
			bool			operator<(const Entity& entity);
			
inline	sf::Vector2<float>	GetCoord() {return _coord;}
};
#endif