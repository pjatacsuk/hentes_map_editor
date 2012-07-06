#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include "TextureManager.h"
#ifndef INC_ENTITY_H
#define INC_ENTITY_H
class Entity {
private:
  int _ID;

public:
  Entity();
  Entity(int id);
  virtual ~Entity()=0;
  virtual void Render(sf::RenderWindow* app,TextureManager* textureManager,sf::Vector2<float> offSet)=0;
  virtual void Update()=0;
  virtual std::string Serialize()=0;
  virtual std::string SerializeForEngine()=0;
  virtual void deSerialize(std::string line)=0;
  //virtual bool operator<(const Entity* entity);
  virtual bool operator==(const Entity* entity);
  //virtual bool operator<(const Entity& entity);

};

#endif