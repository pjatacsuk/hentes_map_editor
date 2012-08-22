#include <string>
#include "ButtonManager.h"
#ifndef INC_DATAFORENGINE_H
#define INC_DATAFORENGINE_H

using namespace resource::consts;

#define NO_ACTION 0x0100

class RectangleBlock;
class ButtonManager;


class DataForEngine {
protected:
	int attributes[20];
	int attribute_count;
	std::string name;
	RectangleBlock* parent;
	ButtonManager*			buttonManager;
public:
	//DataForEngine(){};
	
	DataForEngine(int attribute_c):
	attribute_count(attribute_c)
	{
	//	parent = NULL;
	}
	DataForEngine(const DataForEngine& dfe):
	attribute_count(dfe.attribute_count),
	name(dfe.name)
	{
		for(int i=0;i<dfe.attribute_count;i++) {
			attributes[i] = dfe.attributes[i];
		}
		parent = dfe.parent;
		buttonManager = new ButtonManager(*dfe.buttonManager);
		
	}
	virtual ~DataForEngine(){
		delete buttonManager;
//		parent = NULL;
	};

	
	
	virtual			std::string SerializeForEngine()=0;
	virtual			void		deSerialize(std::string line)=0;
	virtual			std::string GetName()=0;
	virtual void	SetOwner(RectangleBlock* p)=0;
	
	virtual void	CallBack(int i,int value)=0;
			
	ButtonManager*	GetButtonManager() {return buttonManager;}
	int				GetValue(int i) {return attributes[i];}
	virtual void	SetButtonManager(ButtonManager* bman)=0;
};




#endif
