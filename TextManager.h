#ifndef INC_TEXTMANAGER_H
#define INC_TEXTMANAGER_H

//TODO:: FIXÁLNI A RENDERT

#include <queue>
#include <string>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "resource.h"
#include "MyTimer.hpp"
using namespace std;

struct Text {
	
	sf::String string;
	MyTimer timer;

	Text(sf::Vector2<float> crd,std::string txt,sf::Font fnt,int size=28,int time=0):
	timer(time) {
		string = sf::String(txt,fnt,size);
	}
	
	void StartTimer() {
		timer.StartTimer();
	}
	bool is_started() {
		return timer.is_started();
	}
};

class TextManager {
private:
	vector<Text>	texts; 
	
	
public:
	sf::Font		font;

	TextManager(std::string source);
	~TextManager();
	void	DisplayText(sf::RenderWindow* app);
	void	Add(sf::Vector2<float> crd,std::string txt,int time,int size);
};
#endif