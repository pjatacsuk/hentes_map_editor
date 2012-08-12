#include "Font.h"
#include <list>
#ifndef INC_FONTMANAGER_H
#define INC_FONTMANAGER_H

namespace FontManagerType {
	typedef std::list<Font*>::iterator iterator;
}
class FontManager {
	
private:
	std::list<Font*>		font_list;
	sf::RenderWindow*	target;
public:
	FontManager(sf::RenderWindow* target_window);
	FontManager();
	~FontManager();
	
	inline void SetTargetWindow(sf::RenderWindow* target_window) {target = target_window;}
	
	void	Add(std::string string,int time,sf::Vector2<float> pos = sf::Vector2<float>(0,0),sf::Font = sf::Font::GetDefaultFont());
	void	Render();
	


};









#endif