#include "CircularTextureSelect.h"
#include <iostream>
#include <cmath>
#include "resource.h"
CircularTextureSelect::CircularTextureSelect(TextureManager* textureManager,int radius):
_textureManager(textureManager),
_radius(radius),
_CurrentCircle(0),
_textureNumbers(textureManager->Size())
{
	_Circle = sf::Shape::Circle(sf::Vector2<float>(0,0),radius,sf::Color(48,123,211),2);
	_Circle.EnableFill(true);
	_Circle.EnableOutline(true);
	_Circle.SetColor(sf::Color(0,0,100,190));
	_Circle.SetOutlineWidth(5);
	
	
	_RectSelects = new sf::Shape[_textureNumbers];
	_TextureSprites = new sf::Sprite[_textureNumbers];
	
	if(_textureNumbers > MAX_TEXTURE_PER_CIRCLE ) {		
		if(_textureNumbers % MAX_TEXTURE_PER_CIRCLE != 0)	{								//ha t�bb CTS-re van sz�ks�g
			_CircleNumbers = _textureNumbers / MAX_TEXTURE_PER_CIRCLE + 1;
		} else {
			_CircleNumbers = _textureNumbers / MAX_TEXTURE_PER_CIRCLE;
		}
	} 
	else _CircleNumbers = 1;
	
	for(int i=0;i<_textureNumbers;i++) {
		_RectSelects[i].SetOutlineWidth(3);
		_RectSelects[i].SetColor(sf::Color(23,213,21));
		_RectSelects[i].EnableOutline(true);

		_TextureSprites[i].SetImage(_textureManager->operator[](i));
		_TextureSprites[i].Scale(0.7,0.7);
	}
}

/** a ciklusokn�l kisz�molja mennyi m�g a h�tramarad� text�ra amit ki kell sz�molni**/
int		CircularTextureSelect::RemainingTexture() {
	int ret = _textureNumbers % MAX_TEXTURE_PER_CIRCLE * _CurrentCircle;
		if(ret == 0) ret = 6;
		return _CurrentCircle * MAX_TEXTURE_PER_CIRCLE;
}
/** Meghat�rozza az index alapj�n a selecthez sz�ks�ges rectangle-t,
ezen pontok a k�r oldal�n lesznek **/

sf::Shape	CircularTextureSelect::RectFromIndex(int i,float delta_angle) {
	sf::Shape Rectangles = sf::Shape();

	Rectangles.AddPoint(_Circle.GetCenter());											//h�romsz�g k�zepe

	 sf::Vector2<float> vektor(_Circle.GetCenter().x -
							   _radius * cos((90+i*delta_angle)*PI/180),		//h�romsz�g balcs�cs
							   _Circle.GetCenter().y -
							   _radius * sin((90+i*delta_angle)*PI/180));
	
	// std::cout << _Circle.GetCenter().x << " " << vektor.x << " " << _Circle.GetCenter().y << " " << vektor.y << endl;
		Rectangles.AddPoint(sf::Vector2<float>(_Circle.GetCenter().x -
													_radius * cos((90+i*delta_angle)*PI/180),		//h�romsz�g balcs�cs
													_Circle.GetCenter().y -
													_radius * sin((90+i*delta_angle)*PI/180)));
		
		Rectangles.AddPoint(sf::Vector2<float>(_Circle.GetCenter().x -						//h�romsz�g jobb cs�cs
													_radius * cos((90+(i+1)*delta_angle)*PI/180),
													_Circle.GetCenter().y -
													_radius * sin((90+(i+1)*delta_angle)*PI/180)));
		Rectangles.EnableFill(false);
		Rectangles.EnableOutline(true);
		Rectangles.SetOutlineWidth(1);

		return Rectangles;

}


/** A CTS helyzet�t friss�ti az aktu�lis mouse coordin�t�khoz  **/
void	CircularTextureSelect::UpdatePosition(const int x,const int y) {
	

	_Circle.SetCenter(x,y);										// CTS k�zepe
	if(_CircleNumbers == 1) {
		_texturePerCurrentCircle = _textureNumbers;
	} else {
		_texturePerCurrentCircle = _textureNumbers % MAX_TEXTURE_PER_CIRCLE * _CurrentCircle;
		if(_texturePerCurrentCircle == 0) _texturePerCurrentCircle = 6;
	}

	
	float delta_angle = 360 / _texturePerCurrentCircle;				// CTS -en v�laszthat� text�r�k sz�ma
//	float delta_angle = 60;											// prob�lgat�sb�l marad bent
	for(int i = 0;
		    i < _texturePerCurrentCircle;
			i++) 
	{
				
				_RectSelects[i] = RectFromIndex(i,delta_angle);
		
	}
	UpdateTexturePositions();

}


/** a text�r�kat a megfelel� helyre igaz�tja **/
void CircularTextureSelect::UpdateTexturePositions() {
	for(int i = 0;
		    i < _texturePerCurrentCircle; 
			i++) 
	{

		sf::Vector2<float> p2  = _RectSelects[i].GetPointPosition(_RectSelects[i].GetNbPoints()-2);
		sf::Vector2<float> p3  = _RectSelects[i].GetPointPosition(_RectSelects[i].GetNbPoints()-1);
		sf::Vector2<float> center((p3.x - p2.x)/2,(p3.y - p2.y)/2);					//k�z�ppont kisz�m�t�s 
		center +=p2;

		sf::Vector2<float> p1 = _RectSelects[i].GetPointPosition(_RectSelects[i].GetNbPoints()-3);

		sf::Vector2<float> real_coord((center.x - p1.x)/2,(center.y - p1.y)/2);
		real_coord += p1;

		real_coord -= sf::Vector2<float>(resource::consts::BLOCK_SIZE/3,resource::consts::BLOCK_SIZE/3);

		if(_texturePerCurrentCircle == 2) {
			if(i % 2 == 0) {
				real_coord += sf::Vector2<float>(_radius/2,0);
			} else {
				real_coord -= sf::Vector2<float>(_radius/2,0);
			}
		}

		_TextureSprites[i + RemainingTexture()].SetPosition(real_coord);
		
	}

}
/** kisz�molja a sz�get, ahol a 0 a k�r legfels� pontja, 180 a legals�, k�zte egyenletesen n�vekszik **/
float CircularTextureSelect::ComputeAngle(sf::Vector2<float> origo,sf::Vector2<float> point) {
	if(origo != point) {
			point.x -= origo.x;
			point.y -= origo.y;
			
			float szog =  atan2(point.x,point.y)*180/PI;			//sima tan sz�g meghat�roz�s
			if(szog < 0) {											//buhera hogy 0-t�l 366ig menjen a sz�g
				szog = 180 + szog * -1;
				return szog;
			}	else	{
				szog = 180 - szog;
				return szog;
			}
						
		}
	return -10000000;												//kiakad�s miatt

}

/** az eg�r koordin�t�i alapj�n kisz�m�tja a kiv�lasztand� textur�t **/
int CircularTextureSelect::SelectTexture(sf::RenderWindow* target) {
	float x = target->GetInput().GetMouseX();
	float y = target->GetInput().GetMouseY();
	for(int i = 0;
		    i < _texturePerCurrentCircle;
			i++) 
	{

		sf::Vector2<float> p2  = _RectSelects[i].GetPointPosition(_RectSelects[i].GetNbPoints()-2);
		sf::Vector2<float> p3  = _RectSelects[i].GetPointPosition(_RectSelects[i].GetNbPoints()-1);
	//	std::cout << p2.x << " " << p2.y << endl;
		sf::Vector2<float> origo(_Circle.GetCenter());
		sf::Vector2<float> mouse(x,y);

		float angle = ComputeAngle(origo,p2);
		float angle2 = ComputeAngle(origo,p3);
		float angle_mouse = ComputeAngle(origo,mouse);
		
			if(angle2 == 0) angle2 = 360;
			if(angle_mouse > angle && angle_mouse < angle2) {
				return i + RemainingTexture();					// ha m�r a 2. , 3. k�rbe vagyunk
			} 
			
		
	
	//	std::cout << "m: " << angle_mouse << " 3 "  << angle2 << " 2 " << angle << endl;
		}
		return 0;

		
		
}
// TODO: a rectes m�veleteket sz�tszedni k�l�n oszt�lyba
	
	
/** render **/
void CircularTextureSelect::Render(sf::RenderWindow* target) {
	
	target->Draw(sf::Shape::Circle(_Circle.GetCenter(),100,sf::Color(0,60,180,220)));

	for(int i = 0;
		    i < _texturePerCurrentCircle;
			i++) 
	{
		
	
		//target->Draw(_RectSelects[i]);
		sf::Shape line = sf::Shape::Line(_RectSelects[i].GetPointPosition(0),
										_RectSelects[i].GetPointPosition(1),
										1,
										sf::Color(0,0,0));
		sf::Shape line2 = sf::Shape::Line(_RectSelects[i].GetPointPosition(0),
										  _RectSelects[i].GetPointPosition(2),
										  1,
										  sf::Color(0,0,0));
		target->Draw(line);
		target->Draw(line2);
		target->Draw(_TextureSprites[ i + RemainingTexture()]);		//ha m�r a 2. 3. ... k�rbe vagyunk
	//	sf::Sprite texture(_textureManager->operator[](i),center);
	//	target->Draw(texture);

	}
}
/** a circle-ek l�peget�se **/
void CircularTextureSelect::SetCurrentCircle(int direction) {
	if(direction == resource::UP) {
		_CurrentCircle = (_CurrentCircle + 1) % (_CircleNumbers);
	} else {
		if(_CurrentCircle - 1 < 0) {
			_CurrentCircle = _CircleNumbers - 1;					
																	
																	
		} else {
			_CurrentCircle = _CurrentCircle - 1 % _CircleNumbers;
		}

	}
	UpdateTexturePositions();

}