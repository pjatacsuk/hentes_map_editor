#ifndef INC_TEXTURE_MANAGER
#define INC_TEXTURE_MANAGER

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
class TextureManager {
private:
	
	map<int,sf::Image> textures;
public:
	TextureManager(string str);
	TextureManager();
	~TextureManager();

	inline	int		Size() const {return textures.size();}

	void			Add(int type,sf::Image image);
	void			Add(std::string source);
	void			Add(int type,std::string source);
	void			Free_Texture(int type);
	sf::Image&		operator[](int i);
	//const sf::Image&		operator[](int i) const;
	
};


#endif