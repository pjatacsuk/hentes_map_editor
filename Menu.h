#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include "RectangleBlock.h"
#include "EntityManager.h"

using namespace EntityManagerTypes;
#ifndef INC_MENU_H
#define INC_MENU_H

class Menu {
private:
	sf::RenderWindow*		target;
	std::string*			maps;
	EntityManager*			rblocks;
	sf::String*				strings;
	int						count;
	
public:

	Menu(sf::RenderWindow* trgt);
	~Menu();
	
	void					Render();
	void					Update();
	std::string				Loop();

	std::string				CheckIntersection(sf::Vector2<float> p);

};





#endif