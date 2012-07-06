#include "Block.h"
#include <cstring>
#include "resource.h"
#include "TextureManager.h"
#include <sstream>
using namespace resource::function;

Block::Block(int type,sf::Vector2<float> coord):
_type(type),
_coord(coord),
Entity(0){
	
}


Block::Block() {

}
void Block::Render(sf::RenderWindow* app,TextureManager* textureManager,sf::Vector2<float> offSet) {
	sf::Sprite sprite(textureManager->operator[](_type),_coord - offSet);
	app->Draw(sprite);
}

void Block::Update() {

}

std::string Block::Serialize() {
	
	std::stringstream oss;
	oss << "1 " << _coord.x << " " << _coord.y << " " << _type << " ";
	return oss.str();
}

void Block::deSerialize(std::string line) {
	
	char* tmp = new char[line.length()+1];
	strcpy(tmp,line.c_str());
	tmp = strtok(tmp," ");
	tmp = strtok(NULL," ");
	_coord.x = atoi(tmp);							// X coord
	
	tmp = strtok(NULL," ");					// Y coord
	_coord.y = atoi(tmp);

	tmp = strtok(NULL," ");					// Type
	_type = atoi(tmp);
	
}

bool Block::operator<(const Entity* entity) {
	const Block* blck = dynamic_cast<const Block*>(entity);
	return true;
}

bool Block::operator==(const Entity* entity) {
	const Block* block = dynamic_cast<const Block*>(entity);
	if(block == NULL) return false;
	if(block->_type == _type && block->_coord.x == _coord.x && block->_coord.y == _coord.y) {
		return true;
	}
	return false;
}

bool Block::operator<(const Entity& entity) {
	return true;
}