#include "Entity.h"
#include <SFML\Graphics.hpp>
#include "resource.h"
#include "DataForEngine.h"
#include "ButtonManager.h"
#ifndef INC_RECTANGLEBLOCK_H

#define INC_RECTANGLEBLOCK_H
using namespace resource;

enum {UpLeft,UpRight,DownLeft,DownRight};
enum {GATEWAY,PLATFORM,WEAPON,AMMO,MONSTER};

class DataForEngine;
class PlatformData;
class WeaponData;
class AmmoData;
class MonsterData;
class GatewayData;

class RectangleBlock : public Entity {
private:
	sf::Shape				rect;			//"hitbox" egyben pos
	sf::Sprite				sprite;			//sprite a kirajzoláshoz
	bool					hit[4];
	int						defType;
	int						EngineType;
	DataForEngine*			data;

public:
	friend DataForEngine;
	friend PlatformData;
	friend WeaponData;
	friend MonsterData;
	friend AmmoData;
	friend GatewayData;
	

	RectangleBlock(sf::Shape r,int type);
	RectangleBlock();
	~RectangleBlock();

	void					Render(sf::RenderWindow*,TextureManager* textureManager,sf::Vector2<float>);
	void					RenderInfo(sf::RenderWindow* target,sf::Vector2<float> offSet );
	std::string				Serialize();
	std::string				SerializeForEngine();
	void					deSerialize(std::string line);

	inline	void			SetHit(int i){ if(hit[i]) hit[i] = false; else hit[i] = true;}	
	bool					operator==(const Entity* entity);

	sf::Sprite				CopySprite(sf::Sprite&,sf::Vector2<float>);
	void					Update();

	bool					RectangleEquality(const sf::Shape&, const sf::Shape&); 
	bool					PointIntersect(sf::Vector2<float> p);
	void					RenderHitLine(sf::RenderWindow*,sf::Vector2<float>);

	void					SetDataForEngine(int type);

	inline	ButtonManager*	GetButtonManager() {return data->GetButtonManager();}				
};



#endif
