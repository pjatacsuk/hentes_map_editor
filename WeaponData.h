#include "DataForEngine.h"
#include "resource.h"
#include <sstream>
#ifndef INC_WEAPONDATA_H
#define INC_WEAPONDATA_H


using namespace resource::function;



class WeaponData: public DataForEngine {
private:

public:
	WeaponData();
	~WeaponData();

	std::string SerializeForEngine();
	std::string GetName();

	void SetOwner(RectangleBlock* p);
	void SetButtonManager(ButtonManager* bman);

	void CallBack(int i,int value);
	void AddChangeTypeMenu();

};




#endif