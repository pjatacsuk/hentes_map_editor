#include "InfoManager.h"



InfoManager::InfoManager():
offSetString(sf::String()),
objectListString(sf::String()),
mouseString(sf::String()),
textureString(sf::String()),
mapNameString(sf::String()),
sum(0){
	for(int i=0;i<5;i++) block_count[i] = 0;
	offSetString.SetSize(22);
	offSetString.SetColor(sf::Color(61,116,191));
	InitSprite(0,offSetString);

	

	objectListString.SetSize(17);
	objectListString.SetColor(sf::Color(61,116,191));
	InitSprite(1,objectListString);

	mouseString.SetSize(22);
	mouseString.SetColor(sf::Color(61,116,191));
	InitSprite(2,mouseString);
	
	textureString.SetSize(20);
	textureString.SetColor(sf::Color(61,116,191));
	InitSprite(3,textureString);

	mapNameString.SetSize(18);
	mapNameString.SetColor(sf::Color(61,116,191));
	InitSprite(4,mapNameString);

	
	
	
}

void	InfoManager::InitSprite(int i,sf::String from) {
	sprites[i] = sf::Sprite(resource::globalTexture->instance()->GetTexture(resource::function::GetSpriteID("BOX_TEXTURE")),
		from.GetPosition());
	sprites[i].SetScale(from.GetRect().GetWidth()/sprites[i].GetSize().x,
		from.GetRect().GetHeight()/sprites[i].GetSize().y);

}

void	InfoManager::ReInitSprites() {
	InitSprite(0,offSetString);
	InitSprite(1,objectListString);
	InitSprite(2,mouseString);
	InitSprite(3,textureString);
	InitSprite(4,mapNameString);
}
std::string InfoManager::GetObjectCountString() {
	stringstream os;
	os << "Ammo: " << block_count[AMMO] << "\n";
	os << "Weapon: " << block_count[WEAPON] << "\n";
	os << "Monster: " << block_count[MONSTER] << "\n";
	os << "Platform: " << block_count[PLATFORM] << "\n";
	os << "GATEWAY: " << block_count[GATEWAY] << "\n";
	return os.str();
}

void InfoManager::SetMapName(std::string mapname)  {
	mapNameString.SetText(mapname);
	mapNameString.SetPosition((resource::consts::SCREEN_WIDTH - mapNameString.GetRect().GetWidth()) * 1/2 ,
		resource::consts::SCREEN_HEIGHT - mapNameString.GetRect().GetHeight() - 2);
}

void InfoManager::UpdateString(const sf::Vector2<float>& offSet,const int& mouse_x,const int& mouse_y,const int& block_type) {
	stringstream os;
	os << "OffSet: " << "x: "<< offSet.x << " y: " << offSet.y;
	offSetString.SetText(os.str());
	offSetString.SetPosition(resource::consts::SCREEN_WIDTH - offSetString.GetRect().GetWidth(),0);

	os = stringstream();
	os << "Object count: " << sum << "\n";
	os << GetObjectCountString();
	objectListString.SetText(os.str());
	objectListString.SetPosition(2,2);

	os = stringstream();
	os << "x: " << mouse_x << " y: " << mouse_y;
	mouseString.SetText(os.str());
	mouseString.SetPosition(resource::consts::SCREEN_WIDTH - mouseString.GetRect().GetWidth(),
							resource::consts::SCREEN_HEIGHT - mouseString.GetRect().GetHeight());

	textureString.SetText(resource::consts::texture_names[block_type]);
	textureString.SetPosition(0 + 2,resource::consts::SCREEN_HEIGHT - textureString.GetRect().GetHeight() - 1);

	ReInitSprites();

}

void InfoManager::Update(const sf::Vector2<float>& offSet,const int& mouse_x,const int& mouse_y,const int& block_type) {
	UpdateString(offSet,mouse_x + offSet.x,mouse_y + offSet.y,block_type);
}



void InfoManager::Render(sf::RenderWindow* target) {
	for(int i=0;i<5;i++) target->Draw(sprites[i]);

	target->Draw(offSetString);
	target->Draw(objectListString);
	target->Draw(mouseString);
	target->Draw(textureString);
	target->Draw(mapNameString);


}