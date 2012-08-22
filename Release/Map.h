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




class Map {
private:
	EntityManager*	blocks;
	bool			sortFlag;
	Entity*			cornerBlocks[6];
public:
	friend Editor;
	friend SaveToEngine;
  Map(std::string source,TextureManager* textureManager);
  Map();
  ~Map();
  void				Render(sf::RenderWindow* app,TextureManager* textureManager,sf::Vector2<float> offSet);
  void				Update();
  void				Push(Entity* blck);
  void				Remove(Entity* blck);
  void				Remove(sf::Vector2<float>);
  ButtonManager*	OnRightClick(sf::Vector2<float> mouse); 
  void				OpenMapFromFile(std::string path,TextureManager* textureManager);
  Entity*			GetTopLeft();
  Entity*			GetTopRight();
  Entity*			GetDownLeft();
  Entity*			GetDownRight();

  Entity*			Get(Entity* entity);
  
};
#endif