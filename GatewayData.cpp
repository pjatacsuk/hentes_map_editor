#include "GatewayData.h"
#include "RectangleBlock.h"

GatewayData::GatewayData():
DataForEngine(1)
{
		for(int i=0;i<attribute_count;i++) {
		attributes[i] = 0;
	}
	name = "SPAWN";
}

GatewayData::~GatewayData() {

}

std::string GatewayData::SerializeForEngine() {
	std::stringstream os;

	os << name << " ";

	sf::Vector2<float> rect_pos = Transform(parent->rect.GetPointPosition(DownLeft));		//átalakítás
	os << rect_pos.x				<< " " <<			rect_pos.y					 << " ";				//x y

	return os.str();
}

std::string GatewayData::GetName() {
	return name;
}

void	GatewayData::SetOwner(RectangleBlock* p) {
	parent = p;
}

void	GatewayData::CallBack(int index, int value) {
	if(index == NO_ACTION || value == NO_ACTION) {
		return;
	}

	if(index == GATEWAYTYPE) {
		if(value == SPAWN) {
			name = "SPAWNPLACE";
		} else if(value == END) {
			name = "ENDLEVELBUTTON";
		}
	}

	if(index == buttonManager->GetSize()) {
		parent->SetDataForEngine(value);
	}
}

void	GatewayData::SetButtonManager(ButtonManager* bman) {
	buttonManager = bman;

	buttonManager->Add(GATEWAYTYPE,"GWayType",this);
	buttonManager->GetLast().SetValue(NO_ACTION);
	buttonManager->GetLast().SetIndex(NO_ACTION);

	buttonManager->GetLast().AddButtonManager();
	
	ButtonManager* subBman = buttonManager->GetLast().GetButtonManager();

	subBman->Add(GATEWAYTYPE,"SPAWN",this);
	subBman->GetLast().SetValue(SPAWN);

	subBman->Add(GATEWAYTYPE,"END",this);
	subBman->GetLast().SetValue(END);

	AddChangeTypeMenu();
}

void	GatewayData::AddChangeTypeMenu() {

	buttonManager->Add("Type",this);
	buttonManager->GetLast().SetValue(NO_ACTION);
	buttonManager->GetLast().SetIndex(NO_ACTION);

	buttonManager->GetLast().AddButtonManager();
	ButtonManager* bman = buttonManager->GetLast().GetButtonManager();
	int index = buttonManager->GetSize();
	bman->Add(index,"Platform",this);
	bman->GetLast().SetValue(PLATFORM);

	bman->Add(index,"Weapon",this);
	bman->GetLast().SetValue(WEAPON);
	
	bman->Add(index,"Monster",this);
	bman->GetLast().SetValue(MONSTER);

	bman->Add(index,"Ammo",this);
	bman->GetLast().SetValue(AMMO);
}