#include "MonsterData.h"
#include "RectangleBlock.h"

MonsterData::MonsterData():
DataForEngine(4)
{
	for(int i=0;i<attribute_count;i++) {
		attributes[i] = 0;
	}
	name = "MONSTER";
}

MonsterData::~MonsterData() {

}

std::string MonsterData::SerializeForEngine() {
	std::stringstream os;
	//MONSTERTYPE kíírása
	os << name << " ";
	
	//pos kiírása
	sf::Vector2<float> rect_pos = Transform(parent->rect.GetPointPosition(DownLeft));		//átalakítás
	os << rect_pos.x				<< " " <<			rect_pos.y		<< " ";				//x y
	
	//sprite kiírása
	os << (*resource::globalTextureNames->instance())[parent->defType] << " ";
	
	//élet kiírása
	os << attributes[HEALTH] << " ";
	
	//tipus specifikus dolog kiírása
	if(attributes[MONSTERTYPE] == CONTACT) {
		os << attributes[DAMAGE] << " ";
	} else if(attributes[MONSTERTYPE] == SHOOTER) {
		os << attributes[MONSTERWEAPON] << " ";
	}
	//monstertipus kiírása
	if(attributes[MONSTERTYPE] == CONTACT) {
		os << "CONTACT" << " ";
	} else {
		os << "SHOOTER" << " ";
	}
	
	
	
	//méret kiírása
	os << parent->sprite->GetSize().x << " " << parent->sprite->GetSize().y;
	return os.str();

}


std::string MonsterData::GetName() {
	return name;
}

void	MonsterData::SetOwner(RectangleBlock* p) {
	parent = p;
}

void MonsterData::CallBack(int index,int value) {
	if(index == NO_ACTION || value == NO_ACTION) {
		return;
	}

	if(index == MONSTERTYPE) {
		attributes[MONSTERTYPE] = value;
		delete buttonManager;
		buttonManager = NULL;
		SetButtonManager(new ButtonManager(sf::Vector2<float>(parent->rect.GetPointPosition(UpLeft))));
	}
	if(index == DAMAGE) {
		if(value == 1) {
			attributes[DAMAGE] += 50;
		}
		else if(value ==0) {
			if((attributes[DAMAGE] - 50) < 0) return;
			attributes[DAMAGE] -= 50;
		}
	}
	if(index == WEAPONTYPE) {
		attributes[WEAPONTYPE] = value;
	}
	if(index == HEALTH) {
		if(value == 1) {
			attributes[HEALTH] += 50;
		}
		else if(value ==0) {
			if((attributes[HEALTH] - 50) < 0) return;
			attributes[HEALTH] -= 50;
		}
	}
	if(index == buttonManager->GetSize()) {
		parent->SetDataForEngine(value);
	}

	

}


void MonsterData::SetButtonManager(ButtonManager* bman) {
	buttonManager = bman;
	//1 menu gomb, 1 almenüvel
	buttonManager->Add(MONSTERTYPE,"MonsterT",this);
	buttonManager->GetLast().SetIndex(NO_ACTION);
	buttonManager->GetLast().SetValue(NO_ACTION);
	buttonManager->GetLast().AddButtonManager();
	
	ButtonManager* subBman = buttonManager->GetLast().GetButtonManager();
	subBman->Add(MONSTERTYPE,"contact",this);
	subBman->GetLast().SetValue(0);
	
	subBman->Add(MONSTERTYPE,"shooter",this);
	subBman->GetLast().SetValue(1);
	//************************ *//

	//* health inc, health dec *//
	 buttonManager->AddIncDecSubMenu(HEALTH,"Health",this);
	//**************************//

	if(attributes[MONSTERTYPE] == CONTACT) {
			//* damage inc, damage dec *//
		buttonManager->AddIncDecSubMenu(DAMAGE,"Damage",this);


	} else if(attributes[MONSTERTYPE] == SHOOTER) {
		/* weaopn type -ok */
		buttonManager->Add(MONSTERWEAPON,"M.WTYPE",this);

		buttonManager->GetLast().SetValue(NO_ACTION);
		buttonManager->GetLast().SetIndex(NO_ACTION);
	
		buttonManager->GetLast().AddButtonManager();
		ButtonManager* subBman = buttonManager->GetLast().GetButtonManager();
	
		subBman->Add(MONSTERWEAPON,"0",this);
		subBman->GetLast().SetValue(0);
	
		subBman->Add(MONSTERWEAPON,"1",this);
		subBman->GetLast().SetValue(1);

		subBman->Add(MONSTERWEAPON,"2",this);
		subBman->GetLast().SetValue(2);
		/*weapon typeok */
	}
	AddChangeTypeMenu();

}

void MonsterData::AddChangeTypeMenu() {
	// ENNEK KELL LENNI AZ UTOLSÓ MENUPONTNAK AMIT HOZZÁADUNK HOGY MÜKÖDJÖN
	// LASD CALLBACK function
		buttonManager->Add("Type",this);
	buttonManager->GetLast().SetValue(NO_ACTION);

	buttonManager->GetLast().AddButtonManager();

	ButtonManager* bman = buttonManager->GetLast().GetButtonManager();
	int	index = buttonManager->GetSize();
	
	bman->Add(index,"Platform",this);
	bman->GetLast().SetValue(PLATFORM);
	
	bman->Add(index,"Ammo",this);
	bman->GetLast().SetValue(AMMO);

	bman->Add(index,"Weapon",this);
	bman->GetLast().SetValue(MONSTER);

	bman->Add(index,"Gateway",this);
	bman->GetLast().SetValue(GATEWAY);
}

void	MonsterData::deSerialize(std::string line) {
	char tmpname[50];
	int  rect_pos[2];
	char spritename[100];
	int  health;
	int	 specific_attribute;
	char type[100];
	int	 sprite_size[2];

	sscanf(line.c_str(),"%s %d %d %s %d %d %s %d %d",
		&tmpname,&rect_pos[0],&rect_pos[1],
		&spritename,&health,
		&specific_attribute,&type,&sprite_size[0],
		&sprite_size[1]);
	//rect pos már be van rakva globálisan mindennél, ezért sprite nagyságával fogja létrehozni
	attributes[HEALTH] = health;
	if(parent->sprite != NULL) parent->sprite = new sf::Sprite();
	parent->sprite->SetPosition(rect_pos[0],rect_pos[1]);
	parent->defType = GetSpriteID(spritename);

	if(strcmp(type,"SHOOTER") == 0) {
		attributes[MONSTERTYPE] = SHOOTER;
		attributes[WEAPONTYPE] = specific_attribute;

	}
	if(strcmp(type,"CONTACT") == 0) {
		attributes[MONSTERTYPE] = CONTACT;
		attributes[DAMAGE] = specific_attribute;
	}


}