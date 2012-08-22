#include "Entity.h"
#include <SFML\Graphics.hpp>
#include "resource.h"
#include "DataForEngine.h"
#include "ButtonManager.h"
#ifndef INC_RECTANGLEBLOCK_H

#define INC_RECTANGLEBLOCK_H
using namespace resource;

enum {UpLeft,UpRight,DownLeft,DownRight};


class DataForEngine;
class PlatformData;
class WeaponData;
class AmmoData;
class MonsterData;
class GatewayData;

class RectangleBlock : public Entity {
private:
	sf::Shape				rect;			//"hitbox" egyben pos
	sf::Sprite*				sprite;			//sprite a kirajzoláshoz
	bool					hit[4];
	int						defType;
	int						EngineType;
	DataForEngine*			data;
	bool					renderInfoFlag;

public:
	friend DataForEngine;
	friend PlatformData;
	friend WeaponData;
	friend MonsterData;
	friend AmmoData;
	friend GatewayData;
	

	RectangleBlock(sf::Shape r,int type,TextureManager* textureManager,bool render_info=true,bool ForEngineFlag=true);
	RectangleBlock(std::string str,TextureManager* textureManager);
	RectangleBlock(const RectangleBlock& );
	RectangleBlock();
	~RectangleBlock();

	bool					operator<(const Entity* rect);


	inline	sf::Sprite*		GetSprite() const {return sprite;}

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
	void					SetDataForEngine(int type,DataForEngine* );
	void					SetDataForEngine(std::string line);
	inline	ButtonManager*	GetButtonManager() {return data->GetButtonManager();}	
	inline	int				GetType() {return EngineType;}
	
	inline	void			SetRenderInfoFlag(bool b){renderInfoFlag = b;}
	inline	bool			GetRenderInfoFLag() {return renderInfoFlag;}

};



#endif
