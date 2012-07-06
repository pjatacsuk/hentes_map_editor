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

struct Comparator
{
	bool operator() (const sf::Vector2<float>& a,const sf::Vector2<float>& b) {
		if(a.x < b.x ) return true;
		if(a.x == b.x) {
			if(a.y < b.y) {
				return true;
			} else {
				return false;
			}
		}
		return false;
	}
};


class Map {
private:
	EntityManager*	blocks;
	std::map<sf::Vector2<float>,bool,Comparator> coll_boxes;
public:
	friend Editor;
	friend SaveToEngine;
  Map(std::string source);
  Map();
  ~Map();
  void				Render(sf::RenderWindow* app,TextureManager* textureManager,sf::Vector2<float> offSet);
  void				Update();
  void				Push(Entity* blck);
  void				Remove(Entity* blck);
  void				Remove(sf::Vector2<float>);
  void				GenerateCollBoxes();
  bool				GetColBox(sf::Vector2<float> coord);
  ButtonManager*	OnRightClick(sf::Vector2<float> mouse); 

  Entity*			Get(Entity* entity);
  
};
#endif