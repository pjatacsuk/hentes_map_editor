#include "SaveToEngine.h"

SaveToEngine::SaveToEngine(std::string output,Map* map):
_map(map) {

}


SaveToEngine::~SaveToEngine() {

}

void SaveToEngine::SaveStart() {
	
	file.open("test.txt");
	for(EntityManagerTypes::iterator it = _map->blocks->begin();
		it != _map->blocks->end();
		it++) {
			stringstream os;
			os << (*it)->SerializeForEngine() << "\r\n";
			file << os.str();
	}
	file.close();
}