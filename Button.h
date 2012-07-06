#include <SFML\Graphics.hpp>
#include <string>
#include <SFML\Window.hpp>
#include "resource.h"

#ifndef INC_BUTTON_H
#define INC_BUTTON_H


using namespace resource::consts;

class DataForEngine;
class ButtonManager;
class Button {
private:
	sf::Rect<float>		rect;
	sf::Shape			shape;
	sf::String			string;
	ButtonManager*		buttonManager;
	DataForEngine*		parent;
	int					index;
	int					value;

public:
	bool				active;
	bool				dynamic;

	Button();
	~Button();
	Button(sf::Vector2<float> p1,std::string str);
	Button(const Button& b);

	void		UpdatePosition(sf::Vector2<float> p1);

	void		Render(sf::RenderWindow* target,sf::Vector2<float> offSet);
	bool		operator==(const Button& button);
	
	
	
	void		AddButtonManager();
	
	void		SetParent(DataForEngine* p);

	inline		sf::Rect<float> GetRect() const {return rect;}
	inline		void			SetText(std::string str) {string = sf::String(str);}
	inline		DataForEngine*  GetParent() {return parent;}
	inline		ButtonManager*	GetButtonManager() const {return buttonManager;}
	inline		void			SetValue(int v) {value = v;}
	inline		int				GetValue() {return value;}
	inline		void			SetIndex(int i) {index = i;}
	inline		int				GetIndex()		{return index;}
};




#endif