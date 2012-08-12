#include "Button.h"
#include "ButtonManager.h"
#include "DataForEngine.h"
Button::Button(sf::Vector2<float> p1,std::string str):
active(false),
dynamic(false){
	rect = sf::Rect<float>(p1.x,p1.y,p1.x+BUTTON_WIDTH,p1.y+BUTTON_HEIGHT);
	shape = sf::Shape::Rectangle(p1,
								 sf::Vector2<float>(p1.x+BUTTON_WIDTH,
													p1.y+BUTTON_HEIGHT),
													sf::Color(128,128,255),1,sf::Color(0,0,0));
	
	buttonManager = NULL;
	

}

Button::Button():
dynamic(false),
active(false){
	string = sf::String("");
}

Button::~Button() {
	delete buttonManager;
}

Button::Button(const Button& b):
rect(b.rect),
shape(b.shape),
string(b.string),
index(b.index),
value(b.value),
dynamic(b.dynamic){
	parent = b.parent;
	if(b.GetButtonManager() != NULL) {
		const ButtonManager* tmp = b.GetButtonManager();
		buttonManager = new ButtonManager(*tmp);
	} else
	{
		buttonManager = NULL;
	}
	
}



void	Button::Render(sf::RenderWindow* target,sf::Vector2<float> offSet) {
	
		sf::Shape tmp(shape);
		tmp.SetPosition(shape.GetPosition() - offSet);
	//	tmp.SetOutlineWidth(1);
		
		target->Draw(tmp);
		if(buttonManager != NULL) {
			buttonManager->Render(target,offSet);
		}
		sf::String strtmp(string);
		strtmp.SetPosition(string.GetPosition().x - offSet.x,string.GetPosition().y - offSet.y);
		if(dynamic) {
			int data = parent->GetValue(index);
			stringstream os;
			os << data;
			strtmp.SetText(os.str());
		}
		target->Draw(strtmp);


	


}

void	Button::UpdatePosition(sf::Vector2<float> p1) {

	rect = sf::Rect<float>(p1.x,p1.y,p1.x+BUTTON_WIDTH,p1.y+BUTTON_HEIGHT);
	shape = sf::Shape::Rectangle(p1,
								 sf::Vector2<float>(p1.x+BUTTON_WIDTH,
													p1.y+BUTTON_HEIGHT),
								 sf::Color(128,128,255),
								 1,
								 sf::Color(0,0,0));
	string.SetPosition(p1.x + 4,
					  p1.y + 5);
	string.SetSize(12);
	string.SetStyle(sf::String::Style::Bold);

	if(buttonManager != NULL) {
		buttonManager->UpdatePosition(sf::Vector2<float>(rect.Right+1,rect.Top)); // +1 az outline miatt
	}
}

bool	Button::operator==(const Button& button) {
	if(button.rect.Top == rect.Top) {
		return true;
	}
	return false;
}

void	Button::AddButtonManager() {
	buttonManager = new ButtonManager(sf::Vector2<float>(rect.Right,rect.Top));
	

	///**** debug ****/
//	buttonManager->Add("hello");
//	buttonManager->Add("bello");
	
}

void	Button::SetParent(DataForEngine* p) {
	parent = p;
}