#include "resource.h"
#include "RectangleBlock.h"

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