#include "Map.h"
#include <iostream>
#include "RectangleBlock.h"
#include <fstream>
#include "TextureManager.h"
#include "RectangleBlock.h"
Map::Map(std::string source) {
	blocks = new EntityManager();
	fstream file;
	file.open(source,fstream::in);
	std::string line;
	while(file.eof() != true && getline(file,line)) {
		char* tmp = new char[line.size()+1];
		strcpy(tmp,line.c_str());
		
		tmp = strtok(tmp," ");
		int type = atoi(tmp);
		if(type==1) {
//		Block* blck = new Block();
//		blck->deSerialize(line);
//		blocks->Push(blck);
		} else if(type==2) {
			RectangleBlock* rblck = new RectangleBlock();
			rblck->deSerialize(line);
			blocks->Push(rblck);
		}

		
		delete[] tmp;
	}
	
}

Map::Map() {
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
	blocks->Push(blck);
}

Entity* Map::Get(Entity* entity) {
	
	return blocks->Get(entity);
	
}

void Map::Remove(Entity* entity) {
	blocks->Remove(entity);
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
}

void Map::GenerateCollBoxes() {
	for(EntityManagerTypes::iterator it = blocks->begin();
		it != blocks->end();
		it++) {
			Block* blck = dynamic_cast<Block*>(*it);
			int x = blck->GetCoord().x/resource::consts::BLOCK_SIZE;
			int y = blck->GetCoord().y/resource::consts::BLOCK_SIZE;
			coll_boxes[sf::Vector2<float>(x,y)] = true;
	}
	

}

bool Map::GetColBox(sf::Vector2<float> coord) {
	return coll_boxes[coord];
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