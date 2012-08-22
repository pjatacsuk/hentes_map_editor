#include "DataForEngine.h"
#include "resource.h"
#include <sstream>


using namespace resource::function;


class AmmoData: public DataForEngine {
private:

public:
	AmmoData();
	~AmmoData();

	std::string		SerializeForEngine();
	void			deSerialize(std::string line);
	std::string		GetName();

	void			SetOwner(RectangleBlock* p);
	void			SetButtonManager(ButtonManager* bman);

	void			CallBack(int i,int value);
	void			AddChangeTypeMenu();

};