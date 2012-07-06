#include "RectangleBlock.h"
#include "resource.h"
#include <sstream>
#include "AmmoData.h"
#include "PlatformData.h"
#include "WeaponData.h"
#include "MonsterData.h"
#include "GatewayData.h"
using namespace resource::consts;

RectangleBlock::RectangleBlock(sf::Shape r,int type):
rect(r),
Entity(0),
defType(type),
EngineType(PLATFORM),
data(NULL){
	sprite = sf::Sprite();
	sprite.SetPosition(rect.GetPointPosition(0));
	float scaleX = (rect.GetPointPosition(2).x - rect.GetPointPosition(1).x) /
					resource::consts::BLOCK_SIZE;
	sprite.SetScaleX(scaleX);
	hit[0] = true;
	hit[1] = true;
	hit[2] = true;
	hit[3] = true;



	SetDataForEngine(EngineType);
	data->SetOwner(this);
	
	data->SetButtonManager(new ButtonManager(sf::Vector2<float>(rect.GetPointPosition(UpLeft))));
	
	

}

RectangleBlock::RectangleBlock():
rect(),
Entity(0),
sprite(),
EngineType(PLATFORM),
data(NULL){

}

RectangleBlock::~RectangleBlock() {


}

sf::Sprite	RectangleBlock::CopySprite(sf::Sprite& sprite,sf::Vector2<float> offSet) {
	sf::Sprite ret = sf::Sprite(sprite);
	float scaleX = (rect.GetPointPosition(UpRight).x - rect.GetPointPosition(UpLeft).x) /
					sprite.GetSize().x;
		
	float scaleY = (rect.GetPointPosition(DownRight).y - rect.GetPointPosition(UpRight).y) /
					sprite.GetSize().y;

	ret.Scale(scaleX,scaleY);	
	sf::Vector2<float> new_coord = sprite.GetPosition() - offSet;
	ret.SetPosition(new_coord);
	
	return ret;
	 
	
}

void RectangleBlock::RenderInfo(sf::RenderWindow* target,sf::Vector2<float> offSet) {
	sf::String str(data->GetName(),sf::Font::GetDefaultFont(),15.0f);
	str.SetPosition(rect.GetPointPosition(UpLeft).x - offSet.x + 5,rect.GetPointPosition(UpLeft).y - offSet.y -15);
	str.SetColor(sf::Color::Black);


	if(EngineType == PLATFORM) {
	RenderHitLine(target,offSet);
	}
	target->Draw(str);
}

void	RectangleBlock::Render(sf::RenderWindow* target,TextureManager* textureManager,sf::Vector2<float> offSet) {
	if(sprite.GetImage() == NULL) sprite.SetImage(textureManager->operator[](defType));
	


	target->Draw(CopySprite(sprite,offSet));
	RenderInfo(target,offSet);





}

std::string RectangleBlock::Serialize() {
	std::stringstream os;
	os << "2 ";
	for(int i=0;i<rect.GetNbPoints();i++) {
		sf::Vector2f v = rect.GetPointPosition(i);
		os << v.x << " " << v.y << " ";
	}
	for(int i=0;i<4;i++) {
		os << hit[i] << " ";
	}
	os << defType << " ";
	return os.str();
}

void	RectangleBlock::deSerialize(std::string line) {
	char* tmp = new char[line.length()+1];
	strcpy(tmp,line.c_str());
	

	tmp = strtok(tmp," ");
	
	sf::Vector2<float> crd;
	
	
	for(int i=0;i<4;i++) {
		tmp = strtok(NULL," ");	
		crd.x = atof(tmp);
		
		tmp = strtok(NULL," ");
		crd.y = atof(tmp);

		rect.AddPoint(crd);
	
	}
	for(int i=0;i<4;i++) {
		tmp = strtok(NULL," ");
		hit[i] = atoi(tmp);
	}
	tmp = strtok(NULL," ");
	defType = atoi(tmp);
	
	sprite = sf::Sprite();
	sprite.SetPosition(rect.GetPointPosition(0));
	float scaleX = (rect.GetPointPosition(2).x - rect.GetPointPosition(1).x) /
					resource::consts::BLOCK_SIZE;
	sprite.SetScaleX(scaleX);
	
	


	SetDataForEngine(EngineType);
//	data->SetOwner(this);

//	data->SetButtonManager(new ButtonManager(sf::Vector2<float>(rect.GetPointPosition(UpLeft))));
	

	
}
bool	RectangleBlock::RectangleEquality(const sf::Shape& a, const sf::Shape& b) {
	if(a.GetNbPoints() != b.GetNbPoints() ) return false;

	for(int i=0;i<a.GetNbPoints();i++) {			//egyesével megvizsgáljuk
		if(a.GetPointPosition(i) != b.GetPointPosition(i)) {
			return false;
		}
	}
	return true;
}

/** pont benne van-e a rectblock-ba, a pont nincs osztva a blockkal */
bool	RectangleBlock::PointIntersect(sf::Vector2<float> p) {
		if(p.x > rect.GetPointPosition(UpLeft).x &&
			p.x < rect.GetPointPosition(UpRight).x &&
			p.y > rect.GetPointPosition(UpLeft).y &&
			p.y < rect.GetPointPosition(DownRight).y) {
				return true;
		} else {
			return false;
		}
}



bool	RectangleBlock::operator==(const Entity* entity) {
	const RectangleBlock* rblock = dynamic_cast<const RectangleBlock*>(entity);
	if(rblock == NULL) return false;
	
	if(RectangleEquality(rect,rblock->rect)) {
		return true;
	}

	return false;

}



void RectangleBlock::RenderHitLine(sf::RenderWindow* target,sf::Vector2<float> offSet) {
//***** SFML RAGE QUIT miatt ilyen ronda a kód spagetti. **********//


	sf::Shape lines[4];
	sf::Color color[4];
	
	for(int i=0;i<4;i++) {
		if(hit[i] == true) {
			color[i] = sf::Color::Red;
		}
		else {
			color[i] = sf::Color::Green;
		}
	}

	lines[UP] = sf::Shape::Rectangle(rect.GetPointPosition(UpLeft) - offSet,
						             rect.GetPointPosition(UpRight) - offSet +
						             sf::Vector2<float>(2,2),
								     color[UP]);


	lines[LEFT] = sf::Shape::Rectangle(rect.GetPointPosition(UpLeft) - offSet,
									   rect.GetPointPosition(DownLeft) - offSet +
									   sf::Vector2<float>(2,2),
									   color[LEFT]);
	
	lines[DOWN] = sf::Shape::Rectangle(rect.GetPointPosition(DownLeft) - offSet,
									   rect.GetPointPosition(DownRight) - offSet +
									   sf::Vector2<float>(2,2),
									   color[DOWN]);
	
	lines[RIGHT] = sf::Shape::Rectangle(rect.GetPointPosition(UpRight) - offSet,
										rect.GetPointPosition(DownRight) - offSet +
										sf::Vector2<float>(2,2),
										color[RIGHT]);
	
	for(int i=0;i<4;i++) {
		
		target->Draw(lines[i]);
	}
}


void	RectangleBlock::Update() {

}


std::string	RectangleBlock::SerializeForEngine() {
	return data->SerializeForEngine();
}

void RectangleBlock::SetDataForEngine(int type) {
	if(data != NULL) delete data;
	switch(type) {
	case PLATFORM:
		data = new PlatformData();
		break;
	case WEAPON:
		data = new WeaponData();
		break;
	case AMMO:
		data = new AmmoData();
		break;
	case MONSTER:
		data = new MonsterData();
		break;
	case GATEWAY:
		data = new GatewayData();
		break;

	}
		data->SetOwner(this);
		data->SetButtonManager(new ButtonManager(sf::Vector2<float>(rect.GetPointPosition(UpLeft))));
		EngineType = type;
		
}