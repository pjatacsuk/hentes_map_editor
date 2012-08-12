#include "Map.h"
#include <iostream>
#include "RectangleBlock.h"
#include <fstream>
#include "TextureManager.h"
#include "RectangleBlock.h"
using namespace mapname;
Map::Map(std::string source,TextureManager* textureManager):
sortFlag(false)
{
	blocks = new EntityManager();
	for(int i=0;i<5;i++) block_count[i]  = 0;	
	OpenMapFromFile(source,textureManager);

	//blocks->Sort();
/*	//elsõ block ->sort miatt a legbaloldalibb
	cornerBlocks[mapname::LEFT] = cornerBlocks[TOPLEFT] = dynamic_cast<RectangleBlock*>(*(blocks->begin()))->GetSprite()->GetPosition();
	//utsó block -> sort miatt a legjobboldalibb
	cornerBlocks[mapname::RIGHT] = cornerBlocks[BOTTOMRIGHT] = dynamic_cast<RectangleBlock*>(*(--blocks->end()))->GetSprite()->GetPosition();
	cornerBlocks[BOTTOM] = cornerBlocks[TOP] = cornerBlocks[TOPLEFT];
*/	

}

Map::Map():
sortFlag(false)
{
	blocks = new EntityManager();

}

Map::~Map() {
	delete blocks;
}
/** Map rendelés **/
void Map::Render(sf::RenderWindow* app,TextureManager* textureManager,sf::Vector2<float> offSet) {
	for(EntityManagerTypes::iterator it = blocks->begin();
		it != blocks->end();
		it++) {
			
			(*it)->Render(app,textureManager,offSet);								//block-ok egyenkénti kirendelelése
	}
}

void Map::Push(Entity*  blck) {
	sf::Vector2<float> new_pos  = dynamic_cast<RectangleBlock*>(blck)->GetSprite()->GetPosition();

	
	if(new_pos.x < cornerBlocks[mapname::LEFT].x)		cornerBlocks[mapname::LEFT]		=	cornerBlocks[TOPLEFT] = new_pos;
	if(new_pos.y < cornerBlocks[TOP].y)					cornerBlocks[TOP]				=	new_pos;
	if(new_pos.x > cornerBlocks[mapname::RIGHT].x)		cornerBlocks[mapname::RIGHT]	=	cornerBlocks[BOTTOMRIGHT] = new_pos;
	if(new_pos.y > cornerBlocks[BOTTOM].y)				cornerBlocks[BOTTOM]			=	new_pos;
	
	blocks->Push(blck);
	sortFlag = true;
}

Entity* Map::Get(Entity* entity) {
	
	return blocks->Get(entity);
	
}

void Map::Remove(Entity* entity) {
	blocks->Remove(entity);
	sortFlag = true;
}

void Map::Remove(sf::Vector2<float> p) {
	for(EntityManagerTypes::iterator it = blocks->begin();
		it != blocks->end();
		it++) {
			RectangleBlock* tmp = dynamic_cast<RectangleBlock*>(*it);
			if(tmp != NULL) {
				if( tmp->PointIntersect(p) == true) {
					blocks->Remove(it);
					return;
				}

			}
		
	}
	sortFlag = true;
}


ButtonManager* Map::OnRightClick(sf::Vector2<float> mouse) {
		

		for(EntityManagerTypes::iterator it = blocks->begin();
		it != blocks->end();
		it++) {
			RectangleBlock* tmp = dynamic_cast<RectangleBlock*>(*it);
			if(tmp != NULL) {
				if( tmp->PointIntersect(mouse) == true) {
					tmp->GetButtonManager()->UpdatePosition(mouse);
					tmp->GetButtonManager()->active = true;
					return tmp->GetButtonManager();
				}
			}
		
	}
		
}

void Map::OpenMapFromFile(std::string path,TextureManager* textureManager) {
	fstream file;
	file.open(path,fstream::in);
	std::string line;
	bool first = true;			//cornerBlockok feltöltése az elsõ elemmel
	while(file.eof() != true && getline(file,line)) {
		Push(new RectangleBlock(line,textureManager));	
		//a tipus számláló növelése
		
		if(first) {
			for(int i=0;i<6;i++) cornerBlocks[i] = dynamic_cast<RectangleBlock*>(*blocks->begin())->GetSprite()->GetPosition();
			first = false;
		}
	}
}

sf::Vector2<float> Map::GetTopLeft() {
/*	if(sortFlag) {
		blocks->Sort();
	}*/
	return cornerBlocks[TOPLEFT];
}

sf::Vector2<float> Map::GetDownRight() {
	/*if(sortFlag) {
		blocks->Sort();
	}*/
	return cornerBlocks[BOTTOMRIGHT];
}

sf::Vector2<float> Map::GetLeft() {
	return cornerBlocks[mapname::LEFT];
}

Entity* Map::GetTopRight() {
	return NULL;
}

sf::Vector2<float> Map::GetTop() {
	return cornerBlocks[TOP];
}

sf::Vector2<float> Map::GetRight() {
	return cornerBlocks[mapname::RIGHT];
}

sf::Vector2<float> Map::GetBottom() {
	return cornerBlocks[mapname::BOTTOM];
}
