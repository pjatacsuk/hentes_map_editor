#include "Font.h"

Font::Font() {
	text = new sf::String();
	timer = sf::Clock();
	timer.Reset();
}

Font::~Font() {
	delete text;
}

Font::Font(std::string string,int time,sf::Vector2<float> pos ,sf::Font font):
display_time(time){
	text = new sf::String(string,font);
	text->SetPosition(pos);
	timer = sf::Clock();
	timer.Reset();
}

Font::Font(const Font& fnt):
display_time(fnt.display_time){
	text = new sf::String(*fnt.text);
	timer = sf::Clock(fnt.timer);
	
}


bool	Font::ReadyToDie() {
	if(timer.GetElapsedTime() >= display_time) {
		return true;
	}
	else {
		return false;
	}
}

