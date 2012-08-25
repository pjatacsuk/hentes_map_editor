
#include "Block.h"
#include "Map.h"
#include "Game.h"
#include <QtGui/QApplication>
#include <Qt/qframe.h>
#include "qt_proba.h"

#include "graphics-qt.hpp"
//#include "graphics-qt.hpp"
int main( int argc, char* args[] )
{
	QApplication a(argc,args);

	// Create the main frame
	qt_proba w;
	w.show();
	
	//MyCanvas* SFMLView = new MyCanvas(w.GetUi().sfmlframe, QPoint(20, 20), QSize(360, 360));
	//SFMLView->show();

	   Game* MyGame = new Game(w.GetUi().sfmlframe, QPoint(0, 0), QSize(1024, 768));
	   MyGame->show();
//	   resource::consts::myTextureManager = new TextureManager("./textures.txt");
//   MyGame->GameLoop();

//   delete myTextureManager;
    return a.exec();    
}