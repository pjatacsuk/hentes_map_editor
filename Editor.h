
#ifndef INC_EDITOR_H
#define INC_EDITOR_H

#include <vector>
#include "Block.h"
#include "Map.h"
#include <string>
#include "TextureManager.h"
#include "RectangleBlock.h"
#include "SaveToEngine.h"
#include "ButtonManager.h"
#include "CircularTextureSelect.h"
using namespace std;

enum {NORMAL,WATER};

class Editor {
private:
  Map*						_map;
  bool						running;
  sf::Vector2<float>		offSet;
  int						block_type;
  sf::Sprite				mouse_sprite;
  std::string				mapName;
  sf::Sprite				bg_sprite;
  sf::Image					bg_image;
  
  RectangleBlock*			select_rblock;
  
  bool						mouse_button_pressed;
  
 // CircularTextureSelect*	CTS;
  ButtonManager*			actualButtonManager;
  TextureManager*			textureManager;
  sf::RenderWindow*			target;
  int						mouse_x,mouse_y;
  bool						q_down;
  bool						mouse_down;
  std::string				current_map;
 // SaveToEngine				save_engine;

  
  
public:
  Editor();
  Editor(std::string source,TextureManager* tman,sf::RenderWindow* app);
  ~Editor();
  bool			Loop();
  void			Update();
  void			Render();

  void			RenderInfo();

  void			Save(std::string output);
 // void			TextureSelectionsUP();
 // void			TextureSelectionsDOWN();
  

  void			AddLineOfBlock(int& x,int& y,int& n_x,int& n_y);
  void			RemoveRectangleLineOfBlock(sf::Vector2<float>);
  void			UpdateMouse(sf::RenderWindow* target,sf::Event& Event,int& moues_x,int& mouse_y);

  void			UpdateSelectSprite(int x, int y);

  void			GotoTopLeft();
  void			GotoDownRight();
  void			GotoStart();
  void			GotoLeft();
  void			GotoRight();
  void			GotoTop();
  void			GotoBottom();

  inline		void SetBlockType(int i) {block_type = i;}
  inline		std::string GetCurrentMap() {return current_map;}
};
#endif