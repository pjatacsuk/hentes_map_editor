#include "resource.h"
#include <fstream>
#include <sstream>
#include "Map.h"

#ifndef INC_SAVETO_ENGINE 
#define INC_SAVETO_ENGINE


class SaveToEngine{
private:
	ofstream	file;
	std::string mapname;
	Map*		_map;
public:
	SaveToEngine(std::string output,Map*);
//	SaveToEngine();
	~SaveToEngine();

	void SaveStart();

	

};


#endif INC_SAVETO_ENGINE