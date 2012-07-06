#include "AmmoData.h"
#include "RectangleBlock.h"

AmmoData::AmmoData():
DataForEngine(2)
{
	for(int i=0;i<attribute_count;i++) {
		attributes[i] = 0;
	}
	name = "AMMO";
}

AmmoData::~AmmoData() {

}

std::string AmmoData::SerializeForEngine() {
	std::stringstream os;

	os << name << " ";
	
	sf::Vector2<float> rect_pos = Transform(parent->rect.GetPointPosition(DownLeft));		//átalakítás
	os << rect_pos.x				<< " " <<			rect_pos.y					 << " ";				//x y
	os << attributes[WEAPONTYPE]	<< " " <<			attributes[AMOUNT]			 <<" ";
	return os.str();

}

std::string AmmoData::GetName() {
	return name;
}

void	AmmoData::SetOwner(RectangleBlock* p) {
	parent = p;
}

void	AmmoData::CallBack(int index,int value) {
	if(index == NO_ACTION) return;
	
	if(index == WEAPONTYPE) {
		attributes[WEAPONTYPE] = value;
	} 
	if(index == AMOUNT) {
		if(value == 1) {
			attributes[AMOUNT] += 50;
			
		}
		else {
			if((attributes[AMOUNT] - 50) < 0) return;
			attributes[AMOUNT] -= 50;
		}
	}
	if(index == buttonManager->GetSize()) {
		parent->SetDataForEngine(value);
	}

}

void	AmmoData::SetButtonManager(ButtonManager* bman) {
	buttonManager	=	bman;
	buttonManager->Add(WEAPONTYPE,"WTYPE",this);

	buttonManager->GetLast().SetValue(NO_ACTION);
	buttonManager->GetLast().SetIndex(NO_ACTION);
	
	buttonManager->GetLast().AddButtonManager();
	ButtonManager* subBman = buttonManager->GetLast().GetButtonManager();
	
	subBman->Add(WEAPONTYPE,"0",this);
	subBman->GetLast().SetValue(0);
	
	subBman->Add(WEAPONTYPE,"1",this);
	subBman->GetLast().SetValue(1);

	subBman->Add(WEAPONTYPE,"2",this);
	subBman->GetLast().SetValue(2);

	
	/*buttonManager->GetLast().AddButtonManager();
	subBman = buttonManager->GetLast().GetButtonManager();

	subBman->Add(AMOUNT," INC",this);
	subBman->GetLast().SetValue(1);



	subBman->Add(AMOUNT," DEC",this);
	subBman->GetLast().SetValue(0);

	subBman->GetLast().AddButtonManager();
	subBman->GetLast().GetButtonManager()->Add(AMOUNT,"",this);
	subBman->GetLast().GetButtonManager()->GetLast().SetValue(0);
	subBman->GetLast().GetButtonManager()->GetLast().dynamic = true;
	*/
	buttonManager->AddIncDecSubMenu(AMOUNT,"Amount",this);

	AddChangeTypeMenu();
	
}

void	AmmoData::AddChangeTypeMenu() {
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

	bman->Add(index,"Gateway",this);
	bman->GetLast().SetValue(GATEWAY);
}