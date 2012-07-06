#include "ButtonManager.h"
#include "DataForEngine.h"
ButtonManager::ButtonManager() {


}

ButtonManager::ButtonManager(sf::Vector2<float> tl):
top_left(tl),
active(false){

}

ButtonManager::ButtonManager(const ButtonManager& b):
rect(b.rect),
shape(b.shape),
top_left(b.top_left){
	buttons = vector<Button>(b.buttons);
}


void	ButtonManager::Add(std::string str) {
		
		
	buttons.push_back(Button(sf::Vector2<float>(top_left.x,
							 top_left.y + BUTTON_HEIGHT * buttons.size()),
							 str));

	rect = sf::Rect<float>(top_left.x,
						   top_left.y,
						   top_left.x + BUTTON_WIDTH,
						   top_left.y + BUTTON_HEIGHT * buttons.size());
	shape = sf::Shape::Rectangle(top_left,
								 sf::Vector2<float>(rect.Right,rect.Bottom),
								 sf::Color(128,128,0));
}

void	ButtonManager::Add(int index,std::string str,DataForEngine* p) {
	
	
	Add(str,p);
	
	buttons.back().SetIndex(index);
	buttons.back().SetText(str);
	buttons.back().SetParent(p);
}

void ButtonManager::Add(std::string str,DataForEngine* p) {
	Add("");
	buttons[buttons.size() - 1].SetText(str);
	buttons[buttons.size() - 1].SetParent(p);

}


void	ButtonManager::Remove(Button& button) {
	for(vector<Button>::iterator it = buttons.begin();
		it != buttons.end();
		it++) {
			if( (*it) == button) {
				buttons.erase(it);
			}

	}

}

void ButtonManager::UpdatePosition(sf::Vector2<float> pos) {
	rect = sf::Rect<float>(pos.x,
						   pos.y,
						   pos.x + BUTTON_WIDTH,
						   pos.y + BUTTON_HEIGHT * buttons.size());
	shape = sf::Shape::Rectangle(pos,
								 sf::Vector2<float>(rect.Right,rect.Bottom),
								 sf::Color::Cyan);
	int i=0;
	for(vector<Button>::iterator it = buttons.begin();
		it != buttons.end();
		it++) {
			(*it).UpdatePosition(sf::Vector2<float>(rect.Left,rect.Top + i*BUTTON_HEIGHT));
			i++;
	}

}

bool ButtonManager::SubButtonManagerMouseOver(sf::Vector2<float> mouse) {
	for(vector<Button>::iterator it = buttons.begin();
		it != buttons.end();
		it ++) {
			
			if((*it).GetRect().Contains(mouse.x,mouse.y) ) {
				if( (*it).active ) {
						return true;
					}
				} else {
					if( (*it).GetButtonManager() != NULL) {
						if( (*it).GetButtonManager()->active ) {
							return (*it).GetButtonManager()->SubButtonManagerMouseOver(mouse);
						}
					}
			}
			
			
			
	}
	return false;
}

void ButtonManager::UpdateOnMouseOver(sf::Vector2<float> mouse) {
	for(vector<Button>::iterator it = buttons.begin();
		it != buttons.end();
		it ++) {
			
			if((*it).GetRect().Contains(mouse.x,mouse.y) ) {
				if( (*it).GetButtonManager() != NULL) {
					if( (*it).active ) {
						(*it).GetButtonManager()->active = true;
					}
				}
			
			} else {
				if( (*it).GetButtonManager() != NULL) {
					if( (*it).GetButtonManager()->active ) {
						(*it).GetButtonManager()->active = 
							(*it).GetButtonManager()->SubButtonManagerMouseOver(mouse);
					}
				}
			}
			
	}
}

ButtonManager* ButtonManager::SubButtonManagerMouseClick(sf::Vector2<float> mouse,int index) {
	int i=index;
	ButtonManager* ret = NULL;
	for(vector<Button>::iterator it = buttons.begin();
		it != buttons.end();
		it ++) {
			
			if((*it).GetRect().Contains(mouse.x,mouse.y) && (*it).active ) {
				(*it).GetParent()->CallBack((*it).GetIndex(),(*it).GetValue());
				
				return NULL;									//ha null, akkor jobb clickre mindig kilépünk
																//ha it akkor marad ha a területen van
			} else {
				if ( (*it).GetButtonManager() != NULL && (*it).active) {
					ret = (*it).GetButtonManager()->SubButtonManagerMouseClick(mouse,i);
					
				}
			}
			i++;
	}
	return ret;
}

ButtonManager* ButtonManager::UpdateOnMouseClick(sf::Vector2<float> mouse) {
	int i=0;
	ButtonManager* ret = NULL;
	for(vector<Button>::iterator it = buttons.begin();
		it != buttons.end();
		it ++) {
			
			if((*it).GetRect().Contains(mouse.x,mouse.y) && (*it).active ) {
				(*it).GetParent()->CallBack((*it).GetIndex(),(*it).GetValue());
				return this;									//ha null, akkor jobb clickre mindig kilépünk
																//ha it akkor marad ha a területen van
			} else {
				if ( (*it).GetButtonManager() != NULL) {
					if( (*it).GetButtonManager()->active )  {
							ret = (*it).GetButtonManager()->SubButtonManagerMouseClick(mouse,i);
							return ret;
					}
					
				}
			}
			i++;
	}
	return ret;
}

void	ButtonManager::Render(sf::RenderWindow* target, sf::Vector2<float> offSet) {
	if(active) {
		sf::Shape tmp = sf::Shape(shape);
		tmp.SetPosition(shape.GetPosition() - offSet);
		target->Draw(tmp);
		for(vector<Button>::iterator it = buttons.begin();
			it != buttons.end();
			it++) {
				(*it).Render(target,offSet);
		}
	}
}

Button& ButtonManager::operator[](int i) {
	for(vector<Button>::iterator it = buttons.begin();
		it != buttons.end();
		it++) {
			if( (*it).GetIndex() == i) {
				return (*it);
			}

	}
}

void ButtonManager::AddIncDecSubMenu(int type,std::string str,DataForEngine* p) {
	//* health inc, health dec *//
	Add(type,str,p);
	buttons.back().SetIndex(NO_ACTION);
	buttons.back().SetValue(NO_ACTION);
	buttons.back().AddButtonManager();
	
	ButtonManager* subBman = buttons.back().GetButtonManager();

	subBman->Add(type," INC",p);
	subBman->GetLast().SetValue(1);



	subBman->Add(type," DEC",p);
	subBman->GetLast().SetValue(0);
	//* health kijelzõ *//
	subBman->GetLast().AddButtonManager();
	subBman->GetLast().GetButtonManager()->Add(type,"",p);
	subBman->GetLast().GetButtonManager()->GetLast().SetValue(0);
	subBman->GetLast().GetButtonManager()->GetLast().dynamic = true;

}