#include "DataForEngine.h"
#include "resource.h"
#include <sstream>

#ifndef INC_MONSTERDATA_H
#define INC_MONSTERDATA_H

enum {CONTACT,SHOOTER};

using namespace resource::function;


class MonsterData:public DataForEngine {
private:

public:
	MonsterData();
	~MonsterData();

	std::string SerializeForEngine();
	std::string GetName();

	void SetOwner(RectangleBlock* p);
	void SetButtonManager(ButtonManager* bman);

	void CallBack(int i,int value);
	void AddChangeTypeMenu();


	


};







#endif
