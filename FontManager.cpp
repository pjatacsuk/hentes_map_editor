#include "FontManager.h"

using namespace FontManagerType;
FontManager::FontManager(sf::RenderWindow* target_window)
{
	target = target_window;
	font_list = std::list<Font*>();
}

FontManager::FontManager() {
	
	font_list = std::list<Font*>();
}

FontManager::~FontManager() {
	font_list.clear();
}

void FontManager::Add(std::string string,int time,sf::Vector2<float> pos,sf::Font font) {
	font_list.push_front(new Font(string,time,pos,font));
//	(*font_list.begin())->GetText()->SetFont(font);
}

void FontManager::Render() {
	for(iterator it=font_list.begin();it != font_list.end();it++) {
		if((*it)->ReadyToDie() == true) {
			it = font_list.erase(it);
			if(it == font_list.end()) {
				return;
			}
			
		} else {
			(*it)->GetText()->SetFont(sf::Font::GetDefaultFont());
			target->Draw(*(*it)->GetText());
		}
	}
}