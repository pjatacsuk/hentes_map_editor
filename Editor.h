#include <vector>
#include "Block.h"
#include "Map.h"
#include <string>
#include "TextureManager.h"
#include "TextManager.h"
#include "ButtonManager.h"
#include "CircularTextureSelect.h"
using namespace std;

enum {NORMAL,WATER};

class Editor {
private:
  Map*						_map;
  bool						running;
  bool						playing;
  sf::Vector2<float>		offSet;
  int						block_type;
  sf::Sprite				mouse_sprite;
  TextManager*				textManager;
  CircularTextureSelect*	CTS;
  bool						right_mouse_clicked;
  ButtonManager*			actualButtonManager;
public:
  Editor();
  Editor(std::string source);
  ~Editor();
  void			Loop(sf::RenderWindow* target,TextureManager* textureManager);
  void			Update();
  void			Render(sf::RenderWindow* target,TextureManager* textureManager);
  void			Save(std::string output);
  
//  void			AddBlock(sf::Event& Event,int& x,int& y);
// void			RemoveBlock(sf::Event& Event,int& x, int& y);

  void			AddLineOfBlock(int& x,int& y,int& n_x,int& n_y);
//  void			RemoveLineOfBlock(int& x,int& y,int& n_x,int& n_y);
  void			RemoveRectangleLineOfBlock(sf::Vector2<float>);
  void			UpdateMouse(sf::RenderWindow* target,TextureManager* textureManager,sf::Event& Event,int& moues_x,int& mouse_y);

};