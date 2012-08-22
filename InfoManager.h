#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <sstream>
#include "resource.h"
#ifndef INC_INFOMANAGER_H
#define INC_INFOMANAGER_H

using namespace resource;

class InfoManager {
private:
	int					block_count[5];
	int					sum;
	sf::Sprite			sprites[5];

	sf::String			offSetString;
	sf::String			objectListString;
	sf::String			mouseString;
	sf::String			textureString;
	sf::String			mapNameString;

public:
	InfoManager();

	inline		void IncCount(int i) {sum++;block_count[i]++;}
	inline		void IncCount(int from,int to) {block_count[from]--;block_count[to]++;}
	inline		void DecCount(int i) {sum--;block_count[i]--;}
				void SetMapName(std::string mapname);

	std::string	GetObjectCountString();

	
	void		InitSprite(int i,sf::String from);
	void		ReInitSprites();

	void		Update(const sf::Vector2<float>& offSet,const int& mouse_x,const int& mouse_y,const int& block_type);
	void		UpdateString(const sf::Vector2<float>& offSet,const int& mouse_x,const int& mouse_y,const int& block_type);
	void		Render(sf::RenderWindow* target);



};






#endif