
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#ifndef INC_FONT_H
#define INC_FONT_H



class Font {
private:
	sf::String*	text;
	sf::Clock	timer;
	int			display_time;

public:
	Font();
	Font(std::string string,int time,sf::Vector2<float> pos = sf::Vector2<float>(0,0),sf::Font font = sf::Font::GetDefaultFont());
	~Font();
	Font(const Font&);
	inline	sf::String*	GetText() 	{return text;}
	inline	sf::Clock	GetClock() const {return timer;}

	bool	ReadyToDie();
};



#endif