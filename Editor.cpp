#include "Editor.h"
#include <iostream>
#include "resource.h"
#include <fstream>
#include "RectangleBlock.h"
#include <math.h>
#include "GamePlay.h"
#include "SaveToEngine.h"

using namespace resource::consts;

Editor::Editor():
offSet(0,0),
block_type(NORMAL),
playing(false){
	_map = new Map();
	textManager = new TextManager("./data/fonts/calibri.ttf");
	CTS = NULL;
	actualButtonManager = NULL;
}

Editor::Editor(std::string source):
offSet(0,0),
block_type(NORMAL),
playing(false){
	_map = new Map(source);
	textManager = new TextManager("./data/fonts/calibri.ttf");
	actualButtonManager = NULL;
	
}

Editor::~Editor() {
	delete _map;
	if(actualButtonManager != NULL) delete actualButtonManager;
	if(textManager != NULL) delete textManager;
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

void Editor::Loop(sf::RenderWindow* target,TextureManager* textureManager) {
	sf::Event Event;
	int x,y;
	bool q_down = false;
	bool mouse_down = false;
		right_mouse_clicked = false;
	SaveToEngine save_engine("engine_map.txt",_map);
	CTS = new CircularTextureSelect(textureManager,100);
	while(running) {
		if(playing) {
			x = target->GetInput().GetMouseX();
			y = target->GetInput().GetMouseY();
			x = (x + offSet.x) / resource::consts::BLOCK_SIZE;
			y = (y + offSet.y) / resource::consts::BLOCK_SIZE;
			Save("gameplaytest.txt");
			Map* gameplay = new Map("./gameplaytest.txt");
			GamePlay* gamePlay = new GamePlay(gameplay,offSet,sf::Vector2<float>(x*resource::consts::BLOCK_SIZE,y*resource::consts::BLOCK_SIZE));
			gamePlay->Loop(target,textureManager);
			delete gamePlay;
			playing = false;
		}

		while(target->GetEvent(Event)) {
			
			switch(Event.Type) {
			case sf::Event::KeyPressed:
				switch(Event.Key.Code) 
					{
						case sf::Key::Escape:
						
							Save("map1.txt");
							textManager->Add(sf::Vector2<float>(50,50),"SAVED",5000,48);
					
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
						case sf::Key::P:
							playing = true;
							break;
						case sf::Key::O:
							save_engine.SaveStart();
							
							break;
						case sf::Key::Q:
							if(q_down != true) {
								q_down = true;
								actualButtonManager = NULL;								
								CTS->UpdatePosition(target->GetInput().GetMouseX(),
								target->GetInput().GetMouseY());
								CTS->_Active = true;
							
							}
								break;
						case sf::Key::X: 
							sf::Vector2<float> mouse(target->GetInput().GetMouseX() + offSet.x,
											target->GetInput().GetMouseY() + offSet.y);
							RemoveRectangleLineOfBlock(mouse);
							actualButtonManager = NULL;
							
							break;
					}
					break;
			case sf::Event::KeyReleased:
				if(Event.Key.Code == sf::Key::Q) {
					CTS->_Active = false;
					q_down = false;
				}
				break;
			}
			/******************************************************** */
			
			
			UpdateMouse(target,textureManager,Event,x,y);
		
			

			/******************************************************** */ 
			if(q_down) {
				block_type = CTS->SelectTexture(target);
			}
			
				
		}

		
		Render(target,textureManager);
		if(q_down) {
			
							CTS->Render(target);
							
		}
		target->Display();
	}
}

void Editor::Render(sf::RenderWindow* target,TextureManager* textureManager) {
	sf::Sprite sprite;
	
	target->Clear(sf::Color(200,200,200));
	for(int x=0; x<resource::consts::SCREEN_WIDTH; x+=resource::consts::BLOCK_SIZE) { 
		sf::Image image(1,resource::consts::SCREEN_HEIGHT,sf::Color(0,0,0));
		sprite.SetImage(image);
		sprite.SetPosition(x,0);
		target->Draw(sprite);
	}
	for(int y=0; y<resource::consts::SCREEN_HEIGHT; y+=resource::consts::BLOCK_SIZE) {
		sf::Image image(resource::consts::SCREEN_WIDTH,1,sf::Color(0,0,0));			
		sprite.SetImage(image);
		sprite.SetPosition(0,y);
		target->Draw(sprite);
	}
	
	_map->Render(target,textureManager,offSet);																	
	if(actualButtonManager == NULL) {									//ha jobb click menu van
		int x,y;														//akkor nem kell mutató
		x = target->GetInput().GetMouseX();
		y = target->GetInput().GetMouseY();
		mouse_sprite.SetImage(textureManager->operator[](block_type));
		mouse_sprite.SetPosition(x - resource::consts::BLOCK_SIZE/2,
						   y - resource::consts::BLOCK_SIZE/2);
		target->Draw(mouse_sprite);
	} else {
		actualButtonManager->Render(target,offSet);
	}

	
	//text rendelés

//	textManager->DisplayText(target);
	
}


void	Editor::RemoveRectangleLineOfBlock(sf::Vector2<float> p) {
	_map->Remove(p);

}
/* LEGACY
void Editor::AddBlock(sf::Event& Event,int& x,int& y) {
			x = Event.MouseButton.X / resource::consts::BLOCK_SIZE;
			y = Event.MouseButton.Y / resource::consts::BLOCK_SIZE; /*
				_map->Push(new Block(block_type,sf::Vector2<float>(x*resource::consts::BLOCK_SIZE + offSet.x,
																   y*resource::consts::BLOCK_SIZE + offSet.y)));			 		
}
*/
/* LEGACI
void Editor::RemoveBlock(sf::Event& Event,int& x,int& y) {

			x = Event.MouseButton.X / resource::consts::BLOCK_SIZE;
			y = Event.MouseButton.Y / resource::consts::BLOCK_SIZE;
			Block* tmp = new Block(block_type,sf::Vector2<float>(x*resource::consts::BLOCK_SIZE + offSet.x,
																 y*resource::consts::BLOCK_SIZE + offSet.y));
			_map->Remove(tmp);

			delete tmp;
			
}
*/
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

		_map->Push(new RectangleBlock(rect,block_type));
		
}
/* LEGACY
void Editor::RemoveLineOfBlock(int& x,int& y,int& n_x,int& n_y) {
			if(n_x != x && n_y == y) {
					for(int i = x;i<=n_x;i++) {
						Block* tmp = new Block(block_type,sf::Vector2<float>(i*resource::consts::BLOCK_SIZE + offSet.x,
									 									   y*resource::consts::BLOCK_SIZE + offSet.y));
						_map->Remove(tmp);
						delete tmp;
					}
				}
				if(n_y != y && n_x == x) {
					for(int i=y;i<=n_y;i++) {
						Block* tmp =new Block(block_type,sf::Vector2<float>(x*resource::consts::BLOCK_SIZE + offSet.x,
									 									   i*resource::consts::BLOCK_SIZE + offSet.y));
						_map->Remove(tmp);
						delete tmp;
					}
				}
		
}
*/
void Editor::UpdateMouse(sf::RenderWindow* target,TextureManager* textureManager,sf::Event& Event,int& x,int& y) {
	if(Event.Type == sf::Event::MouseButtonPressed) {
				//mouse_down = true;
				switch(Event.MouseButton.Button)
				{
				case sf::Mouse::Left: 
						//release-nél van block hozzáadás
						x = Event.MouseButton.X / resource::consts::BLOCK_SIZE;
						y = Event.MouseButton.Y / resource::consts::BLOCK_SIZE;	
					
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
				//mouse_down = false;
		if(actualButtonManager == NULL) {
			int n_x = target->GetInput().GetMouseX() / resource::consts::BLOCK_SIZE;
			int n_y = target->GetInput().GetMouseY() / resource::consts::BLOCK_SIZE;

			if(Event.MouseButton.Button == sf::Mouse::Left) {
				if(actualButtonManager != NULL) {
					
					actualButtonManager = NULL;				// eltüntetjük az elõzõ menut
				} else {
					AddLineOfBlock(x,y,n_x,n_y);
				}
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
					if(CTS->_Active == false) {
						block_type = (block_type + 1) % textureManager->Size();
					} else {
						CTS->SetCurrentCircle(resource::UP);
						CTS->UpdatePosition(target->GetInput().GetMouseX(),
								target->GetInput().GetMouseY());
					}
						//mouse_down = false;
				} else {
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
				//	mouse_down = false;
						
				}

	}
	if(actualButtonManager != NULL ) {
		actualButtonManager->UpdateOnMouseOver(sf::Vector2<float>(target->GetInput().GetMouseX() + offSet.x,
											target->GetInput().GetMouseY() + offSet.y));
	}			
}