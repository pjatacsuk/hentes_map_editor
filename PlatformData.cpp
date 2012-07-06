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

std::string PlatformData::SerializeForEngine() {
		std::stringstream os;
		os << name << " ";
		
		sf::Vector2<float> rect_pos = Transform(parent->rect.GetPointPosition(DownLeft));						//átalakítás
		os << rect_pos.x				<< " " <<			rect_pos.y									<< " ";	//x y
		os << parent->rect.GetPointPosition(DownRight).x - parent->rect.GetPointPosition(DownLeft).x	<< " ";	//width
		os << parent->rect.GetPointPosition(DownRight).y - parent->rect.GetPointPosition(UpRight).y		<< " ";	//height
		os << parent->hit[LEFT]		<< " " <<  parent->hit[UP]		<< " "
		   << parent->hit[RIGHT]	<< " " << parent->hit[DOWN]		<< " ";										//falak
		os << parent->defType		<< " ";																		//spriteID
		sf::Vector2<float> sprite_pos = Transform(parent->sprite.GetPosition() +
												sf::Vector2<float>(0,resource::consts::BLOCK_SIZE));
		os << sprite_pos.x					<< " " <<	sprite_pos.y					 << " ";				//sprite x y
		os << parent->sprite.GetSize().x	<< " " <<	parent->sprite.GetSize().x		 << " ";	
		
		sf::Vector2<float> scale = sf::Vector2<float>();
		
		scale.x =	parent->rect.GetPointPosition(DownRight).x - parent->rect.GetPointPosition(DownLeft).x;
		scale.x = scale.x / parent->sprite.GetSize().x;

		scale.y =	 parent->rect.GetPointPosition(DownRight).y - parent->rect.GetPointPosition(UpRight).y;
		scale.y = scale.y / parent->sprite.GetSize().y;
		
		//sprrite w h
		//os << parent->sprite.GetScale().x	<< " " <<	parent->sprite.GetScale().y		 << " ";	
		os	<< scale.x << " " << scale.y << " ";


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