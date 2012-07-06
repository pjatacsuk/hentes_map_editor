#include <string>
#include "Entity.h"
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

class RectangleBlock;

namespace resource {
#ifndef RESOURCE_H
#define RESOURCE_H
	enum {UP,LEFT,DOWN,RIGHT};
	enum {WEAPONTYPE,AMOUNT};
	enum {MONSTERTYPE,HEALTH,MONSTERWEAPON,DAMAGE};
#endif

	namespace function {
		void  DrawLine(sf::RenderWindow* target,sf::Vector2<float> from,sf::Vector2<float> to);
			
		sf::Vector2<float> Transform(sf::Vector2<float> v);
		sf::Vector2<float> Transform(int x, int y);
			
	}

	namespace consts {
#ifndef res_const
#define res_const
		static const int SCREEN_WIDTH	=	1024;
		static const int SCREEN_HEIGHT	=	768;
		static const int BLOCK_SIZE		=	30;
		static const int SCREEN_EDGE	=	100;		//mikor kell váltani az offSet-et
		static const int GRAVITY		=	5;
		static const int FPS			=	60;
		static const int BUTTON_WIDTH	=	70;
		static const int BUTTON_HEIGHT	=	30;
#endif
	}
	namespace objects {
#ifndef res_objects
#define res_objects
		template<class T> struct lesser {
			bool operator()(const T* x,const T* y) const {
				return (*x) < (*y);
			}
		};

#endif

	}
}
