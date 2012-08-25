#include "Map.h"
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include "EntityManager.h"
#include "QSFMLCanvas.hpp"
#include "TextureManager.h"
#include "Menu.h"
#include "Editor.h"
enum status {MENU,MAPCHOOSE,GAMEPLAY,EDITOR};

class Game : public QSFMLCanvas {
private:
	bool				running;
	sf::RenderWindow*    App;
	Map*				map;
	status				game_status;
	TextureManager*		textureManager;
	std::string			map_path;
	Menu*				menu;
	Editor*				editor;
	
public:
	Game(QWidget* Parent, const QPoint& Position, const QSize& Size);
	~Game();

	void	OnInit();
	void	OnUpdate();
	void	GameMenu();
	void	GameEditor();

};