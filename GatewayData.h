#include "DataForEngine.h"
#include "resource.h"
#include <sstream>


using namespace resource::function;

enum {GATEWAYTYPE};
enum {SPAWN,END};

class GatewayData: public DataForEngine {
private:
	

public:
	GatewayData();
	~GatewayData();

	std::string SerializeForEngine();
	std::string GetName();

	void SetOwner(RectangleBlock* p);
	void SetButtonManager(ButtonManager* bman);

	void CallBack(int i,int value);
	void AddChangeTypeMenu();
};