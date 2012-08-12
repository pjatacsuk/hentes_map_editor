#include "resource.h"
#include "RectangleBlock.h"
#include "InfoManager.h"

void resource::function::DrawLine(sf::RenderWindow* target,sf::Vector2<float> from,sf::Vector2<float> to) {
	sf::Shape line;
	line.AddPoint(from);
	line.AddPoint(to);
	line.SetOutlineWidth(3);
	line.EnableOutline(true);
	line.SetColor(sf::Color());
	target->Draw(line);
	
}


sf::Vector2<float> resource::function::Transform(sf::Vector2<float> v) {
	return sf::Vector2<float>(v.x,(v.y - resource::consts::SCREEN_HEIGHT) * -1);

}
sf::Vector2<float> resource::function::Transform(int x, int y) {
	return sf::Vector2<float>(x, (y - resource::consts::SCREEN_HEIGHT) * -1);
}

int resource::function::GetSpriteID(std:: string name) {
	for(int i=0;i<resource::consts::MAX_TEXTURE;i++) {
		if(texture_names[i] == name) {
			return i;
		}

	}
	return -1;

}

sf::Vector2<float> resource::function::deTransform(sf::Vector2<float> v) {
	return sf::Vector2<float>(v.x,(v.y  * -1) + resource::consts::SCREEN_HEIGHT );
}

void	resource::function::deTransform(sf::Shape& rect) {
	for(int i=0;i<4;i++) {
		rect.SetPointPosition(i,deTransform(rect.GetPointPosition(i)));
	}
}

void	resource::function::deTransform(sf::Sprite& sprite) {
	sprite.SetPosition(sprite.GetPosition() + sf::Vector2<float>(0,sprite.GetSize().y));
	sprite.SetPosition(deTransform(sprite.GetPosition()));
}

resource::objects::GlobalInfoManager::GlobalInfoManager() {
	myInfoManager = new InfoManager();
}

void resource::objects::GlobalInfoManager::Reset() {
	if(myInfoManager != NULL) delete myInfoManager;
	myInfoManager = new InfoManager();
}

resource::objects::GlobalTexture* resource::objects::GlobalTexture::s_instance;
resource::objects::GlobalTextManager* resource::objects::GlobalTextManager::s_instance;
resource::objects::GlobalInfoManager* resource::objects::GlobalInfoManager::s_instance;