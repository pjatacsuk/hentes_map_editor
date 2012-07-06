#include "WeaponData.h"
#include "RectangleBlock.h"
WeaponData::WeaponData():
DataForEngine(1)
{
	for(int i=0;i<attribute_count;i++) {
		attributes[i] = 0;
	}
	name = "WEAPON";
}

WeaponData::~WeaponData() {

}

std::string WeaponData::SerializeForEngine() {
	std::stringstream os;

	os << name << " ";
	
	sf::Vector2<float> rect_pos = Transform(parent->rect.GetPointPosition(DownLeft));		//átalakítás
	os << rect_pos.x				<< " " <<			rect_pos.y		<< " ";				//x y
	os << attributes[WEAPONTYPE] << " ";
	return os.str();

}

std::string WeaponData::GetName() {
	return name;
}

void	WeaponData::SetOwner(RectangleBlock* p) {
	parent = p;
}

void	WeaponData::CallBack(int index,int value) {
	if(index == NO_ACTION) return;
	
	if(index == 0) {
		attributes[WEAPONTYPE] = value;
	} 
	if(index == buttonManager->GetSize()) {
		parent->SetDataForEngine(value);
	}
}

void	WeaponData::SetButtonManager(ButtonManager* bman) {
	buttonManager	=	bman;
	buttonManager->Add(WEAPONTYPE,"WTYPE",this);
	buttonManager->GetLast().SetValue(NO_ACTION);

	buttonManager->GetLast().AddButtonManager();
	ButtonManager* subBman = buttonManager->GetLast().GetButtonManager();
	
	subBman->Add(WEAPONTYPE,"0",this);
	subBman->GetLast().SetValue(0);
	
	subBman->Add(WEAPONTYPE,"1",this);
	subBman->GetLast().SetValue(1);

	subBman->Add(WEAPONTYPE,"2",this);
	subBman->GetLast().SetValue(2);

	
	AddChangeTypeMenu();
}

void	WeaponData::AddChangeTypeMenu() {
	buttonManager->Add("Type",this);
	buttonManager->GetLast().SetValue(NO_ACTION);

	buttonManager->GetLast().AddButtonManager();

	ButtonManager* bman = buttonManager->GetLast().GetButtonManager();
	int	index = buttonManager->GetSize();
	
	bman->Add(index,"Platform",this);
	bman->GetLast().SetValue(PLATFORM);
	
	bman->Add(index,"Ammo",this);
	bman->GetLast().SetValue(AMMO);

	bman->Add(index,"Monster",this);
	bman->GetLast().SetValue(MONSTER);


	bman->Add(index,"Gateway",this);
	bman->GetLast().SetValue(GATEWAY);

}