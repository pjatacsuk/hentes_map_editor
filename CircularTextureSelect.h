#include "TextureManager.h"
#include <SFML\Graphics.hpp>
#ifndef INC_CTS_H
#define INC_CTS_H
#define PI 3.14159265

static const int MAX_TEXTURE_PER_CIRCLE = 24;
class CircularTextureSelect {
private:
	TextureManager* _textureManager;
	sf::Shape		_Circle;
	sf::Shape*		_RectSelects;
	sf::Sprite*		_TextureSprites;
	int				_textureNumbers;
	int				_texturePerCurrentCircle;
	int				_CircleNumbers;
	int				_radius;
	int				_CurrentCircle;
	
public:
	bool			_Active;

	CircularTextureSelect(TextureManager* textureManager,int radius);
	float			ComputeAngle(sf::Vector2<float>,sf::Vector2<float>);

	int				SelectTexture(sf::RenderWindow* target);
	void			UpdatePosition(const int mouse_x,const int mouse_y);
	void			Render(sf::RenderWindow* target);
	sf::Shape		RectFromIndex(int i,float delta_angle);			
	void			UpdateTexturePositions();

	void			SetCurrentCircle(int direction);
	int			RemainingTexture();
};


#endif