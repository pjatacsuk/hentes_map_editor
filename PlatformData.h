#include "DataForEngine.h"
#include "resource.h"
#include <sstream>
#ifndef INC_PLATFORMDATA_H
#define INC_PLATFORMDATA_H

//enum {LEFT,UP,RIGHT,DOWN};

using namespace resource::function;
class PlatformData: public DataForEngine {
private:

public:
	PlatformData();
	~PlatformData();
	
	std::string		SerializeForEngine();
	void			deSerialize(std::string line);
	std::string		GetName();
	void			SetOwner(RectangleBlock* p);
	void			SetButtonManager(ButtonManager* bman);
		
	void			CallBack(int i,int value);
	void			AddChangeTypeMenu();


};





#endif