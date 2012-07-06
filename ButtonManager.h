#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "Button.h"
#include <map>
#include "resource.h"

#ifndef INC_BUTTONMANAGER_H
#define INC_BUTTONMANAGER_H

using namespace resource::consts;
class	DataForEngine;

class ButtonManager{
private:
	sf::Rect<float>							rect;
	sf::Shape								shape;
	vector<Button>							buttons;
	sf::Vector2<float>						top_left;
	
public:
	ButtonManager();
	ButtonManager(sf::Vector2<float> );
	ButtonManager(const ButtonManager& b);

	bool				active;

	void				Add(std::string );
	void				Add(int index,std::string,DataForEngine*);
	void				Add(std::string str,DataForEngine* p);
	void				Remove(Button& );

	void				Render(sf::RenderWindow* ,sf::Vector2<float> );

	void				UpdateOnMouseOver(sf::Vector2<float> );
	ButtonManager*		UpdateOnMouseClick(sf::Vector2<float> );
	bool				SubButtonManagerMouseOver(sf::Vector2<float> );
	ButtonManager*		SubButtonManagerMouseClick(sf::Vector2<float>,int i);				
	void				UpdatePosition(sf::Vector2<float> );
	Button&				operator[](int i);
	inline	int			GetSize() {return buttons.size();}
	inline Button&		GetLast() {return buttons.back();}

	void			AddIncDecSubMenu(int type,std::string str,DataForEngine* p);
	
};

#endif