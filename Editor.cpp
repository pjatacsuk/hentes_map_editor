#include "Editor.h"
#include <iostream>
#include "resource.h"
#include <fstream>
#include "RectangleBlock.h"
#include <math.h>
#include "SaveToEngine.h"
#include "InfoManager.h"
using namespace resource::consts;

Editor::Editor():
offSet(0,0),
block_type(NORMAL),
_map(NULL),
textureManager(NULL),
actualButtonManager(NULL),
mapName(std::string()),
mouse_button_pressed(false),
target(NULL),
q_down(false),
current_map(""),
mouse_down(false)
{
	resource::globalInfoManager->instance()->Reset();

	_map = new Map();
	
	actualButtonManager = NULL;
	//CTS = new CircularTextureSelect(textureManager,100);
	bg_image = sf::Image();
	bg_image.LoadFromFile("./data/images/bg.png");
	bg_sprite = sf::Sprite(bg_image);

	select_rblock = new RectangleBlock();

	
	
	
}

Editor::Editor(std::string source,TextureManager* tman,sf::RenderWindow* app):
offSet(0,0),
block_type(NORMAL),
_map(NULL),
actualButtonManager(NULL),
textureManager(NULL),
mapName(source),
mouse_button_pressed(false),
target(NULL),
q_down(false),
mouse_down(false),
current_map("")
{

	resource::globalInfoManager->instance()->Reset();

	textureManager = tman;
	
	bg_image = sf::Image();
	bg_image.LoadFromFile("./data/images/bg.png");
	bg_sprite = sf::Sprite(bg_image);
	
	select_rblock = new RectangleBlock();
	
	_map = new Map(source,textureManager);
	current_map = source;


	actualButtonManager = NULL;
	//CTS = new CircularTextureSelect(textureManager,100);
	target = app;

	resource::globalTextManager->instance()->SetRenderTarget(target);
	resource::globalInfoManager->instance()->GetInfoManager()->SetMapName(mapName);

	
}

Editor::~Editor() {
	if(_map != NULL)				delete _map;
	if(actualButtonManager != NULL) delete actualButtonManager;
//	if(CTS != NULL)					delete CTS;
	
}

void Editor::Save(std::string output) {
	
	
	fstream file;
	file.open(output,fstream::out);
	for(EntityManagerTypes::iterator it = _map->blocks->begin();
		it != _map->blocks->end();
		it++) 
	{
		file << (*it)->Serialize() << endl;
	}
	file.close();
	
	
}

void Editor::Update() {
	resource::globalInfoManager->instance()->GetInfoManager()->Update(offSet,
																	  target->GetInput().GetMouseX(),
																	  target->GetInput().GetMouseY(),
																	  block_type);
}
bool Editor::Loop() {
	
	//kiválasztott block_type a Qt editorból
	block_type = resource::bridgeToEditor->instance()->GetBlockType();
	
	sf::Event my_event;
	
//	while(running) {
		while(target->GetEvent(my_event)){
			
			switch(my_event.Type) {
			case sf::Event::KeyPressed:
				switch(my_event.Key.Code) 
					{
						case sf::Key::Escape:
						
							return false;
					
							break;
						case sf::Key::Numpad8:
							GotoTop();
							break;
						case sf::Key::Numpad2:
							GotoBottom();
							break;
						case sf::Key::Numpad7:
							GotoTopLeft();
							break;
						case sf::Key::Numpad3:
							GotoDownRight();
							break;
						case sf::Key::Numpad5:
							GotoStart();
							break;
						case sf::Key::Numpad6:
							GotoRight();
							break;

						case sf::Key::Numpad4:
							GotoLeft();
							break;
						case sf::Key::Up:
					//		TextureSelectionsUP();
							break;
						case sf::Key::Down:
					//		TextureSelectionsDOWN();
							break;
						case sf::Key::W:
							offSet.y -= resource::consts::BLOCK_SIZE;
							break;
						case sf::Key::A:
							offSet.x -= resource::consts::BLOCK_SIZE;
						break;

						case sf::Key::S:
							offSet.y  += resource::consts::BLOCK_SIZE;
							break;
						case sf::Key::D:
							offSet.x  += resource::consts::BLOCK_SIZE;
							break;
						case sf::Key::O:
						//	save_engine = SaveToEngine(mapName,_map);
						//	save_engine.SaveStart();
							resource::globalTextManager->instance()->GetFontManager()->Add("Saved",3,sf::Vector2<float>(resource::consts::SCREEN_WIDTH/2-20,0));

							
							break;
						case sf::Key::Q:
					/*		if(q_down != true) {										//texture választó megjelenítése
								q_down = true;
								actualButtonManager = NULL;								//jobb click menü eltüntetése							
								CTS->UpdatePosition(target->GetInput().GetMouseX(),
								                    target->GetInput().GetMouseY());
								CTS->_Active = true;
							
							}*/
								break;
						case sf::Key::X:												//törlés
							sf::Vector2<float> mouse(target->GetInput().GetMouseX() + offSet.x,
											         target->GetInput().GetMouseY() + offSet.y);
							RemoveRectangleLineOfBlock(mouse);
							actualButtonManager = NULL;									//jobb click menü eltüntetése
							
							break;
					}
					break;
			case sf::Event::KeyReleased:
		/*		if(my_event.Key.Code == sf::Key::Q) {
					CTS->_Active = false;
					q_down = false;
				}*/
				break;
			}

			UpdateMouse(target,my_event,mouse_x,mouse_y);
			/* Qt EDITOR MIATT EZT SZÉPEN MEGY LEGACYBA
			if(q_down) {
				block_type = CTS->SelectTexture(target);
			}
			*/
			//Update procedura	
			Update();
		}

		
		Render();
		/*if QT EDITOR MIATT MEGY LEGACYBA
		(q_down) {
			CTS->Render(target);
		}*/
		
//	}
		return true;
}



void Editor::RenderInfo() {
	resource::globalInfoManager->instance()->GetInfoManager()->Render(target);
	
	

}
	
void Editor::Render() {
	
	target->Clear(sf::Color(200,200,200)); 
	target->Draw(bg_sprite);
	_map->Render(target,textureManager,offSet);																	
	if(actualButtonManager == NULL) {									//ha jobb click menu van
		int x,y;														//akkor nem kell mutató
		x = target->GetInput().GetMouseX();
		y = target->GetInput().GetMouseY();
		mouse_sprite.SetImage(textureManager->operator[](block_type));
		mouse_sprite.SetPosition(x - resource::consts::BLOCK_SIZE/2,
						   y - resource::consts::BLOCK_SIZE/2);
		if(!mouse_button_pressed)	target->Draw(mouse_sprite);
	} else {
		actualButtonManager->Render(target,offSet);
	}
	RenderInfo();

	resource::globalTextManager->instance()->GetFontManager()->Render();
	if(mouse_button_pressed)
	select_rblock->Render(target,textureManager,offSet);
	
	
}


void	Editor::RemoveRectangleLineOfBlock(sf::Vector2<float> p) {
	_map->Remove(p);

}
void Editor::AddLineOfBlock(int& x,int& y,int& n_x,int& n_y) {
		
				
		
		
		if(n_x < x) {
			int tmp = x;
			x = n_x;
			n_x = tmp;
		}

		if(n_y < y) {
		  int tmp = y;
		  y = n_y;
		  n_y = tmp;
		}
		sf::Shape rect = sf::Shape();
		sf::Vector2<float> LeftUp(x * BLOCK_SIZE,y * BLOCK_SIZE);
		sf::Vector2<float> RightUp(n_x * BLOCK_SIZE + BLOCK_SIZE,y * BLOCK_SIZE);
		sf::Vector2<float> LeftDown(x * BLOCK_SIZE,n_y * BLOCK_SIZE + BLOCK_SIZE);		
		sf::Vector2<float> RightDown(n_x * BLOCK_SIZE + BLOCK_SIZE,n_y * BLOCK_SIZE + BLOCK_SIZE);

	
		rect.AddPoint(LeftUp + offSet);
		rect.AddPoint(RightUp + offSet);
	

		rect.AddPoint(LeftDown + offSet);
		rect.AddPoint(RightDown + offSet);

		_map->Push(new RectangleBlock(rect,block_type,textureManager));
		
}

void Editor::UpdateMouse(sf::RenderWindow* target,sf::Event& Event,int& x,int& y) {
	if(Event.Type == sf::Event::MouseButtonPressed) {
				switch(Event.MouseButton.Button)
				{
				case sf::Mouse::Left: 
						//release-nél van block hozzáadás
						x = Event.MouseButton.X / resource::consts::BLOCK_SIZE;
						y = Event.MouseButton.Y / resource::consts::BLOCK_SIZE;
						if(actualButtonManager == NULL) {
							mouse_button_pressed = true;
						}
					
					break;
				case sf::Mouse::Right:
					actualButtonManager	=_map->OnRightClick(sf::Vector2<float>(Event.MouseButton.X + offSet.x,
																				Event.MouseButton.Y+offSet.y));
					
					break;
				}
				int n_x = target->GetInput().GetMouseX() / resource::consts::BLOCK_SIZE;
				int n_y = target->GetInput().GetMouseY() / resource::consts::BLOCK_SIZE;
				resource::function::DrawLine(target,sf::Vector2<float>(x,y),sf::Vector2<float>(33,33));	
	}
	if(Event.Type == Event.MouseButtonReleased) {
		if(actualButtonManager == NULL) {
			int n_x = target->GetInput().GetMouseX() / resource::consts::BLOCK_SIZE;
			int n_y = target->GetInput().GetMouseY() / resource::consts::BLOCK_SIZE;

			if(Event.MouseButton.Button == sf::Mouse::Left) {
				if(actualButtonManager != NULL) {
					
					actualButtonManager = NULL;				// eltüntetjük az elõzõ menut
				} else {
					AddLineOfBlock(x,y,n_x,n_y);
				}

				mouse_button_pressed = false;
				
			}
		} else { 
			if(Event.MouseButton.Button == sf::Mouse::Left) {
				actualButtonManager = actualButtonManager->UpdateOnMouseClick(sf::Vector2<float>(target->GetInput().GetMouseX() +offSet.x,
																			   target->GetInput().GetMouseY() + offSet.y));
				
			}
		}
			 
	} 
	if(Event.Type == Event.MouseWheelMoved) {
				if(Event.MouseWheel.Delta > 0) {
				//	TextureSelectionsUP();
				} else {
					//TextureSelectionsDOWN();
						
				}

	}
	if(actualButtonManager == NULL) {
		if(mouse_button_pressed) UpdateSelectSprite(x,y);
	}

	if(actualButtonManager != NULL ) {
		actualButtonManager->UpdateOnMouseOver(sf::Vector2<float>(target->GetInput().GetMouseX() + offSet.x,
											target->GetInput().GetMouseY() + offSet.y));
	}			
}

/*
void Editor::TextureSelectionsUP() {
	if(CTS->_Active == false) {
						block_type = (block_type + 1) % textureManager->Size();
					} else {
						CTS->SetCurrentCircle(resource::UP);
						CTS->UpdatePosition(target->GetInput().GetMouseX(),
								target->GetInput().GetMouseY());
					}
}

void Editor::TextureSelectionsDOWN() {
	if(CTS->_Active == false) {
						if(block_type - 1 < 0) {
							block_type = textureManager->Size() -1;
						} else {
							block_type = block_type - 1 % textureManager->Size();
						}
					} else {
						CTS->SetCurrentCircle(resource::DOWN);
						CTS->UpdatePosition(target->GetInput().GetMouseX(),
								target->GetInput().GetMouseY());
					}
}
*/
void Editor::GotoTopLeft() {
	offSet =  (_map->GetTopLeft() + sf::Vector2<float>(0,_map->GetTop().y - _map->GetTopLeft().y));
}

void Editor::GotoDownRight() {
	offSet = _map->GetDownRight() - sf::Vector2<float>(resource::consts::SCREEN_WIDTH-resource::consts::BLOCK_SIZE,
		resource::consts::SCREEN_HEIGHT-resource::consts::BLOCK_SIZE - (_map->GetBottom().y - _map->GetDownRight().y));

}

void Editor::GotoStart() {
	offSet = sf::Vector2<float>(0,0);
}

void Editor::GotoLeft() {
	offSet = _map->GetLeft() - sf::Vector2<float>(0,resource::consts::SCREEN_HEIGHT/2);
}

void Editor::GotoRight() {
	offSet = _map->GetRight() - (sf::Vector2<float>(resource::consts::SCREEN_WIDTH -resource::consts::BLOCK_SIZE,resource::consts::SCREEN_HEIGHT/2));
}

void Editor::GotoTop() {
	offSet = _map->GetTop() - sf::Vector2<float>(resource::consts::SCREEN_WIDTH/2,0);
}

void Editor::GotoBottom() {
	offSet = _map->GetBottom() - sf::Vector2<float>(resource::consts::SCREEN_WIDTH/2,resource::consts::SCREEN_HEIGHT-resource::consts::BLOCK_SIZE);
}

void Editor::UpdateSelectSprite(int x, int y) {
	int n_x = target->GetInput().GetMouseX() / resource::consts::BLOCK_SIZE;
	int n_y = target->GetInput().GetMouseY() / resource::consts::BLOCK_SIZE;
	
	if(n_x < x) {
			int tmp = x;
			x = n_x;
			n_x = tmp;
		}

		if(n_y < y) {
		  int tmp = y;
		  y = n_y;
		  n_y = tmp;
		}
		sf::Shape rect = sf::Shape();
		sf::Vector2<float> LeftUp(x * BLOCK_SIZE,y * BLOCK_SIZE);
		sf::Vector2<float> RightUp(n_x * BLOCK_SIZE + BLOCK_SIZE,y * BLOCK_SIZE);
		sf::Vector2<float> LeftDown(x * BLOCK_SIZE,n_y * BLOCK_SIZE + BLOCK_SIZE);		
		sf::Vector2<float> RightDown(n_x * BLOCK_SIZE + BLOCK_SIZE,n_y * BLOCK_SIZE + BLOCK_SIZE);

	
		rect.AddPoint(LeftUp + offSet);
		rect.AddPoint(RightUp + offSet);
	


		rect.AddPoint(LeftDown + offSet);
		rect.AddPoint(RightDown + offSet);
		if(select_rblock != NULL) delete select_rblock;
		select_rblock = new RectangleBlock(rect,block_type,textureManager,false,false);
		

}