#include <string>
#include "Entity.h"
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include "FontManager.h"
#include "TextureManager.h"


class RectangleBlock;
class InfoManager;



namespace resource {
#ifndef RESOURCE_H
#define RESOURCE_H
	enum {UP,LEFT,DOWN,RIGHT};
	enum {WEAPONTYPE,AMOUNT};
	enum {GATEWAY,PLATFORM,WEAPON,AMMO,MONSTER};
	enum {MONSTERTYPE,HEALTH,MONSTERWEAPON,DAMAGE};
#endif

	namespace function {
		void  DrawLine(sf::RenderWindow* target,sf::Vector2<float> from,sf::Vector2<float> to);
			
		sf::Vector2<float> Transform(sf::Vector2<float> v);
		sf::Vector2<float> Transform(int x, int y);
		sf::Vector2<float> deTransform(sf::Vector2<float> v);
		sf::Vector2<float> deTransform(int x, int y);
		void deTransform(sf::Shape& rect);
		void deTransform(sf::Sprite& sprite);
		int GetSpriteID(std::string name);
			
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
		static const int MAX_TEXTURE	=	50;
		
		static const std::string map_dir_path = ".\\data\\maps\\";

		
	
//		static TextureManager*  myTextureManager;
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
		class GlobalTexture {
		private:
			TextureManager* myTextureManager;
			static GlobalTexture* s_instance;
			GlobalTexture() {
				myTextureManager = new TextureManager("./textures.txt");

			}
		public:
			static GlobalTexture* instance() {
				if(s_instance==NULL) {
					s_instance = new GlobalTexture();
					
				}
				return s_instance;
			}
			sf::Image& GetTexture(int i) {
				return s_instance->myTextureManager->operator[](i);
			}
			inline TextureManager* GetTextureManager() {
				return myTextureManager;
			}
			
		};

		class GlobalTextManager {
		private:
			FontManager* myFontManager;
			static GlobalTextManager* s_instance;
			GlobalTextManager() {
				myFontManager = new FontManager();
			}
		public:
			static GlobalTextManager* instance() {
				if(s_instance == NULL) {
					s_instance = new GlobalTextManager();
				}
				return s_instance;
			}
			void SetRenderTarget(sf::RenderWindow* rw) {
				myFontManager->SetTargetWindow(rw);
			}
			FontManager* GetFontManager() {return myFontManager;}
			
		};
		
		class GlobalInfoManager {
		private:
			InfoManager* myInfoManager;
			static	GlobalInfoManager* s_instance;
			GlobalInfoManager();

		public:
			static GlobalInfoManager* instance() {
				if(s_instance == NULL) {
					s_instance = new GlobalInfoManager();
				}
				return s_instance;
			}
			InfoManager*	GetInfoManager() {
				return myInfoManager;
			}

			void	Reset();
			

		};
		class TextureNames {
		private:
			static TextureNames* s_instance;
			std::vector<std::string> texture_names;
			TextureNames() 
			{
				
				ifstream file;
				file.open("./textures.txt");

				while(!file.eof() && file.is_open()) {
					stringstream is;
					string str;
						getline(file,str);
						is << str.substr(str.find(" ")+1);
						texture_names.push_back(is.str());
					}
			}

		public:
			static TextureNames* instance() {
				if(s_instance ==NULL) {
					s_instance = new TextureNames();
				}
				return s_instance;
			}
			const std::string& const operator[](const int i) {
				if(i < texture_names.size() &&
					i >= 0) {
				return texture_names[i];
				} else {
					throw  "HIBA";
				}
			}
			int size() {return texture_names.size();}
			

		};


#endif

	}
#ifndef globaltexture
#define globaltexture
	static resource::objects::GlobalTexture* globalTexture = NULL;
	static resource::objects::GlobalTextManager* globalTextManager = NULL;
	static resource::objects::GlobalInfoManager* globalInfoManager = NULL;
	static resource::objects::TextureNames*		globalTextureNames = NULL;
#endif


}
