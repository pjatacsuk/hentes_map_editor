#include <vector>
#include "Block.h"
#include "EntityManager.h"
#include "TextureManager.h"
#include "ButtonManager.h"

#ifndef INC_MAP_H
#define INC_MAP_H
class Editor;
class SaveToEngine;
using namespace EntityManagerTypes;
using namespace std;
namespace mapname{
enum {TOPLEFT,BOTTOMRIGHT,TOP,BOTTOM,LEFT,RIGHT};
}

class Map {
private:
	EntityManager*			blocks;
	bool					sortFlag;
	sf::Vector2<float>		cornerBlocks[6];
	 int						block_count[5];
	 bool					updateObjectListFlag;
public:
	friend Editor;
	friend SaveToEngine;
  Map(std::string source,TextureManager* textureManager);
  Map();
  ~Map();
  void					Render(sf::RenderWindow* app,TextureManager* textureManager,sf::Vector2<float> offSet);
  void					Update();
  void					Push(Entity* blck);
  void					Remove(Entity* blck);
  void					Remove(sf::Vector2<float>);
  ButtonManager*		OnRightClick(sf::Vector2<float> mouse); 
  void					OpenMapFromFile(std::string path,TextureManager* textureManager);
  sf::Vector2<float>	GetTopLeft();
  Entity*				GetTopRight();
  sf::Vector2<float>	GetLeft();
  sf::Vector2<float>	GetDownRight();
  sf::Vector2<float>	GetTop();
  sf::Vector2<float>	GetBottom();
  sf::Vector2<float>	GetRight();

 
 
  Entity*			Get(Entity* entity);
  
};
#endif