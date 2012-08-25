#include "TextureManager.h"

TextureManager::TextureManager(string source) {
	ifstream file;
	file.open(source);

	while(!file.eof()) {
		stringstream is;
		string str;
		getline(file,str);

/*		char* cstr = new char[str.length()+1];
		strcpy(cstr,str.c_str());

		int type = atoi(strtok(cstr," "));
		cstr = strtok(NULL," "); */
		is << "./data/images/" << str.substr(0,str.find(" "));
		Add(is.str());

		//delete cstr;
	}
}

TextureManager::TextureManager() {

}

TextureManager::~TextureManager() {
	
	textures.clear();
}

void TextureManager::Add(int type,sf::Image texture) {
	 textures[type] = texture;
	
}

void TextureManager::Free_Texture(int type) {
	
}

sf::Image& TextureManager::operator[](int i) {
	if(i<0 || i > textures.size()) throw "hiba";
	return textures[i];
}

void TextureManager::Add(std::string source) {
	sf::Image image;
	image.LoadFromFile(source);
	Add(textures.size(),image);
	
	//itt már -1, hogy egyezzen a két index
	texture_paths[textures.size()-1] = source;
}

void TextureManager::Add(int type,std::string source) {
	sf::Image image;
	image.LoadFromFile(source);
	Add(textures.size(),image);
	
}

