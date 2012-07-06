#include "TextManager.h"

TextManager::TextManager(std::string source)
{
	font =  sf::Font();
	if(!font.LoadFromFile(source)) {
		return;
	}
	
	
}

TextManager::~TextManager() {
	texts.clear();
}

void TextManager::DisplayText(sf::RenderWindow* app) {
	
	for(vector<Text>::iterator it = texts.begin();it != texts.end(); it++) {
		if((*it).is_started() == false) {
			(*it).StartTimer();
		}
		
		if((*it).timer.End() == true) {
			
			it = texts.erase(it);
			if(texts.size() ==0) return;
		} 
		else {
		/*SDL_Surface* message = TTF_RenderText_Solid(font,(*it).text.c_str(),textColor);
		resource::function::apply_surface((*it).coord.GetX(),(*it).coord.GetY(),message,target);
		*/
			app->Draw((*it).string);
		}
	}
}

void TextManager::Add(sf::Vector2<float> crd,std::string txt,int time,int size) {
	texts.push_back(Text(crd,txt,font,size,time));
}