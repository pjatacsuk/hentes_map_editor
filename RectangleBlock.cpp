#include "RectangleBlock.h"
#include "resource.h"
#include <sstream>
#include "AmmoData.h"
#include "PlatformData.h"
#include "WeaponData.h"
#include "MonsterData.h"
#include "GatewayData.h"
#include "InfoManager.h"
using namespace resource::consts;

RectangleBlock::RectangleBlock(sf::Shape r,int type,TextureManager* textureManager,bool render_info):
rect(r),
Entity(0),
defType(type),
EngineType(PLATFORM),
data(NULL),
renderInfoFlag(render_info){
	sprite = new sf::Sprite();

	if(sprite->GetImage() == NULL) sprite->SetImage(textureManager->operator[](defType));
	sprite->SetPosition(rect.GetPointPosition(0));
	float scaleX = (rect.GetPointPosition(UpRight).x - rect.GetPointPosition(UpLeft).x) /
			sprite->GetSize().x;
	float scaleY = (rect.GetPointPosition(DownLeft).y - rect.GetPointPosition(UpLeft).y) /
			sprite->GetSize().y;
	sprite->SetScale(scaleX,scaleY);
	hit[0] = true;
	hit[1] = true;
	hit[2] = true;
	hit[3] = true;

	

	SetDataForEngine(EngineType);
	
	
	

}

RectangleBlock::RectangleBlock():
rect(),
Entity(0),
sprite(),
EngineType(PLATFORM),
data(NULL),
renderInfoFlag(false){

}

RectangleBlock::RectangleBlock(const RectangleBlock& rb):
rect(rb.rect),
defType(rb.defType),
EngineType(rb.EngineType),
renderInfoFlag(rb.renderInfoFlag){
	for(int i=0;i<4;i++) hit[i] = rb.hit[i];
	sprite = new sf::Sprite(*rb.sprite);
	SetDataForEngine(rb.EngineType,rb.data);
}

RectangleBlock::RectangleBlock(std::string line,TextureManager* textureManager):
data(NULL),
EngineType(PLATFORM),
renderInfoFlag(true)
{
	/** minden elemnél ez a 3 rész fix, a többi speficikus így azt a DataForEngine kezeli **/
	sf::Vector2<float> DownRightPoint;
	char* tmp = new char[line.size()+1];
	strcpy(tmp,line.c_str());
	tmp = strtok(tmp," ");
	tmp = strtok(NULL," ");
	DownRightPoint.x = atoi(tmp);
	tmp = strtok(NULL," ");
	DownRightPoint.y = atoi(tmp);

//	sscanf(line.c_str(),"%s %d %d",tmp,&DownRightPoint.x,&DownRightPoint.y);
	rect =  sf::Shape();
	rect.AddPoint(DownRightPoint);
	rect.AddPoint(DownRightPoint);
	rect.AddPoint(DownRightPoint);
	rect.AddPoint(DownRightPoint);
	/******************************************************************/
	



	SetDataForEngine(line);


	if(sprite->GetImage() == NULL) sprite->SetImage(textureManager->operator[](defType));
	if(rect.GetPointPosition(DownLeft) == rect.GetPointPosition(DownRight)) {
		//ilyenkor nincs a rectrõl infõ a .map file-ban ezért a sprite nagyságával
		//hozzuk létre
		sf::Vector2<float>	DownLeftPos = rect.GetPointPosition(DownLeft);
		rect.SetPointPosition(UpLeft,DownLeftPos.x,DownLeftPos.y +sprite->GetSize().x );
		rect.SetPointPosition(UpRight,DownLeftPos.x + sprite->GetSize().x ,DownLeftPos.y + sprite->GetSize().y);
		rect.SetPointPosition(DownRight,DownLeftPos.x + sprite->GetSize().x ,DownLeftPos.y);

	}


	resource::function::deTransform(rect);
	resource::function::deTransform(*sprite);

	


}


RectangleBlock::~RectangleBlock() {
	delete sprite;
	delete data;

}

sf::Sprite	RectangleBlock::CopySprite(sf::Sprite& sprite,sf::Vector2<float> offSet) {
	sf::Sprite ret = sf::Sprite(sprite);
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
	} else if(EngineType == AMMO) {
		stringstream os;
		os << data->GetName() << " " << data->GetValue(WEAPONTYPE);
		str.SetText(os.str());
	}
	target->Draw(str);
}

void	RectangleBlock::Render(sf::RenderWindow* target,TextureManager* textureManager,sf::Vector2<float> offSet) {
	
	if(sprite->GetPosition().x - offSet.x > 0 ||
		sprite->GetPosition().x - offSet.x < resource::consts::SCREEN_WIDTH ||
		sprite->GetPosition().y - offSet.y > 0 ||
		sprite->GetPosition().y - offSet.y < resource::consts::SCREEN_HEIGHT) {

			sprite->SetPosition(sprite->GetPosition() - offSet);		//transformálás
			target->Draw(*sprite);
			sprite->SetPosition(sprite->GetPosition() + offSet);		//vissza
			
			//információ renderelése ha a flag true
			if(renderInfoFlag)		RenderInfo(target,offSet);

	}



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
	
	sprite = new sf::Sprite();
	sprite->SetPosition(rect.GetPointPosition(0));
	float scaleX = (rect.GetPointPosition(2).x - rect.GetPointPosition(1).x) /
					resource::consts::BLOCK_SIZE;
	sprite->SetScaleX(scaleX);
	
	


	SetDataForEngine(EngineType);
//	data->SetOwner(this);

//	data->SetButtonManager(new ButtonManager(sf::Vector2<float>(rect.GetPointPosition(UpLeft))));
	delete[] tmp;

	
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
	if(data != NULL) {
		delete data;
		resource::globalInfoManager->instance()->GetInfoManager()->IncCount(EngineType,type);
	} else {
		resource::globalInfoManager->instance()->GetInfoManager()->IncCount(type);
	}
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

void RectangleBlock::SetDataForEngine(std::string line) {
	char* tmp = new char[line.size() + 1];
	strcpy(tmp,line.c_str());

	tmp = strtok(tmp," ");
	int type = 0;

	if(data != NULL) delete data;
	if(strcmp(tmp,"PLATFORM") == 0)	{
		data = new PlatformData();
		type = PLATFORM;
	}
	if(strcmp(tmp,"WEAPON") == 0)	{
		data = new WeaponData();
		type = WEAPON;
	}
	if(strcmp(tmp,"MONSTER") == 0)	{
		data = new MonsterData();
		type = MONSTER;
	}
	if(strcmp(tmp,"SPAWNPLACE") == 0 || strcmp(tmp,"ENDLEVELBUTTON") == 0) {
		data = new GatewayData(); 
		type = GATEWAY;
	}
	if(strcmp(tmp,"AMMO") == 0)	{
		data = new AmmoData();
		type = AMMO;
	}


		data->SetOwner(this);
		data->deSerialize(line);
		data->SetButtonManager(new ButtonManager(sf::Vector2<float>(rect.GetPointPosition(UpLeft))));
		EngineType = type;

		
		resource::globalInfoManager->instance()->GetInfoManager()->IncCount(EngineType);
	
		
}
void RectangleBlock::SetDataForEngine(int type,DataForEngine* d) {
	if(data != NULL) {
		delete data;
		resource::globalInfoManager->instance()->GetInfoManager()->IncCount(EngineType,type);
	}
	switch(type) {
	case PLATFORM:
		data = new PlatformData((*dynamic_cast<PlatformData*>(d)));
		break;
	case WEAPON:
		data = new WeaponData((*dynamic_cast<WeaponData*>(d)));
		break;
	case AMMO:
		data = new AmmoData((*dynamic_cast<AmmoData*>(d)));
		break;
	case MONSTER:
		data = new MonsterData((*dynamic_cast<MonsterData*>(d)));
		break;
	case GATEWAY:
		data = new GatewayData((*dynamic_cast<GatewayData*>(d)));
		break;

	}
		data->SetOwner(this);
		//data->SetButtonManager(new ButtonManager(sf::Vector2<float>(rect.GetPointPosition(UpLeft))));
		//EngineType = type;
		
}

bool	RectangleBlock::operator<(const Entity* rect) {
	const RectangleBlock*	rb = dynamic_cast<const RectangleBlock*>(rect);
	sf::Vector2<float> this_pos = (*this).sprite->GetPosition();
	sf::Vector2<float> rb_pos = rb->sprite->GetPosition();

	if(this_pos.x < rb_pos.x) return true;
	if(this_pos.x == rb_pos.x) {
		if(this_pos.y < rb_pos.y) {
			return true;
		}
	}
	return false;
}