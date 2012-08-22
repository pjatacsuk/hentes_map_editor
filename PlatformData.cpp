#include "PlatformData.h"
#include "RectangleBlock.h"
PlatformData::PlatformData():
DataForEngine(4)
 {
	 for(int i=0;i<attribute_count;i++) {
		 attributes[i] = 0;
	 }
	 name = "PLATFORM";
	 
}
PlatformData::~PlatformData(){

}

void	PlatformData::deSerialize(std::string line) {
	int bhit[4];
	char texturename[50];
	char name[50];
	sf::Vector2<float>	tmp;
	int rect_size[2];
	int sprite_pos[2];
	int	sprite_size[2];
	float	scale[2];
	sscanf(line.c_str(),"%s %d %d %d %d %d %d %d %d %s %d %d %d %d %f %f",&name,&tmp.x,&tmp.y,&rect_size[0],&rect_size[1],
																	&bhit[0],&bhit[1],&bhit[2],&bhit[3],
																	&texturename,
																	&sprite_pos[0],&sprite_pos[1],
																	&sprite_size[0],&sprite_size[1],
																	&scale[0],&scale[1]);
	sf::Vector2<float>	DownLeftPos = parent->rect.GetPointPosition(DownLeft);
	parent->rect.SetPointPosition(UpLeft,DownLeftPos.x,DownLeftPos.y + rect_size[1] );
	parent->rect.SetPointPosition(UpRight,DownLeftPos.x + rect_size[0] ,DownLeftPos.y + rect_size[1]);
	parent->rect.SetPointPosition(DownRight,DownLeftPos.x + rect_size[0] ,DownLeftPos.y);

	parent->sprite = new sf::Sprite();
	parent->sprite->SetPosition(sprite_pos[0],sprite_pos[1]);
	parent->sprite->SetScale(scale[0],scale[1]);

	parent->defType = GetSpriteID(texturename);

	for(int i=0;i<4;i++) {
	parent->hit[i] = bhit[i];
	}
}

std::string PlatformData::SerializeForEngine() {
		std::stringstream os;
		os << name << " ";
		
		sf::Vector2<float> rect_pos = Transform(parent->rect.GetPointPosition(DownLeft));						//átalakítás
		os << rect_pos.x				<< " " <<			rect_pos.y									<< " ";	//x y
		os << parent->rect.GetPointPosition(DownRight).x - parent->rect.GetPointPosition(DownLeft).x	<< " ";	//width
		os << parent->rect.GetPointPosition(DownRight).y - parent->rect.GetPointPosition(UpRight).y		<< " ";	//height
		os << parent->hit[LEFT]		<< " " <<  parent->hit[UP]		<< " "
		   << parent->hit[RIGHT]	<< " " << parent->hit[DOWN]		<< " ";										//falak
		os << (*resource::globalTextureNames->instance())[parent->defType]		<< " ";																		//spriteID
		sf::Vector2<float> sprite_pos = Transform(parent->sprite->GetPosition() +
			sf::Vector2<float>(0,parent->sprite->GetSize().y));
		os << sprite_pos.x					<< " " <<	sprite_pos.y					 << " ";				//sprite x y
		os << parent->sprite->GetSize().x	<< " " <<	parent->sprite->GetSize().x		 << " ";	
		
		/*sf::Vector2<float> scale = sf::Vector2<float>();
		
		scale.x =	parent->rect.GetPointPosition(DownRight).x - parent->rect.GetPointPosition(DownLeft).x;
		scale.x = scale.x / parent->sprite->GetSize().x;

		scale.y =	 parent->rect.GetPointPosition(DownRight).y - parent->rect.GetPointPosition(UpRight).y;
		scale.y = scale.y / parent->sprite->GetSize().y;*/
		
		//sprrite w h
		os << parent->sprite->GetScale().x	<< " " <<	parent->sprite->GetScale().y		 << " ";	
//		os	<< parent->sprite->GetScale().x << " " << scale.y << " ";


	return os.str();
}

std::string PlatformData::GetName() {
	return name;

}

void	PlatformData::SetOwner(RectangleBlock* p) {
	parent = p;
}

void PlatformData::SetButtonManager(ButtonManager* bman) {
	buttonManager = bman;
	/*buttonManager->Add("");
	buttonManager->Add("");
	buttonManager->Add("");
	buttonManager->Add("");

	buttonManager->operator[](RIGHT).SetText("RIGHT");
	buttonManager->operator[](RIGHT).SetText("UP");
	buttonManager->operator[](RIGHT).SetText("LEFT");
	buttonManager->operator[](DOWN).SetText("DOWN");

	buttonManager->operator[](RIGHT).SetParent(this);
	buttonManager->operator[](UP).SetParent(this);
	buttonManager->operator[](LEFT).SetParent(this);
	buttonManager->operator[](DOWN).SetParent(this);*/

	

	buttonManager->Add(UP,"UP",this);
	buttonManager->operator[](UP).SetValue(UP);
	buttonManager->Add(RIGHT,"RIGHT",this);
	buttonManager->operator[](RIGHT).SetValue(RIGHT);
	buttonManager->Add(LEFT,"LEFT",this);
	buttonManager->operator[](LEFT).SetValue(LEFT);
	buttonManager->Add(DOWN,"DOWN",this);
	buttonManager->operator[](DOWN).SetValue(DOWN);

	AddChangeTypeMenu();


}

void PlatformData::CallBack(int i,int value) {
	if(i == buttonManager->GetSize() ) {
		parent->SetDataForEngine(value);
		return;
	} else if(i == NO_ACTION) return;
	parent->SetHit(i);
}

void PlatformData::AddChangeTypeMenu() {
	buttonManager->Add("Type",this);
	buttonManager->GetLast().SetValue(NO_ACTION);
	buttonManager->GetLast().SetIndex(NO_ACTION);
	
	buttonManager->GetLast().AddButtonManager();
	ButtonManager* bman = buttonManager->GetLast().GetButtonManager();
	int index = buttonManager->GetSize();
	bman->Add(index,"Weapon",this);
	bman->GetLast().SetValue(WEAPON);
	
	bman->Add(index,"Ammo",this);
	bman->GetLast().SetValue(AMMO);	
	
	bman->Add(index,"Monster",this);
	bman->GetLast().SetValue(MONSTER);

	bman->Add(index,"Gateway",this);
	bman->GetLast().SetValue(GATEWAY);

}