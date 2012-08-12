#include "Map.h"
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include "EntityManager.h"
#include "TextureManager.h"
enum status {MENU,MAPCHOOSE,GAMEPLAY,EDITOR};

class Game {
private:
	bool				running;
	sf::RenderWindow*    App;
	Map*				map;
	status				game_status;
	TextureManager*		textureManager;
	std::string			map_path;
	
public:
	Game();
	~Game();

	void	Init_Game();
	void	GameLoop();
	void	GameMenu();
	void	GameEditor();

};