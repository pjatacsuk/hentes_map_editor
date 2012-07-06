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
	EntityManager*		entityManager;
	status				game_status;
	TextureManager*		textureManager;
public:
	Game();
	~Game();

	void	Init_Game();
	void	Load_Map(std::string map_source);
	void 	Free_Game();
	void	GameLoop();
	void	GameMenu();
	void	GamePlay();
	void	GameEditor();
	void	MapChoose();

};