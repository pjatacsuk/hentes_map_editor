#include "Menu.h"
#include "resource.h"
#include "dirent.h"

Menu::Menu(sf::RenderWindow* trgt):
target(trgt),
count(0){
		DIR *dir;
	struct dirent *ent;
	dir = opendir (resource::consts::map_dir_path.c_str());
		std::string tmp[50];
		
	if (dir != NULL) {

	  /* print all the files and directories within directory */
	  while ((ent = readdir (dir)) != NULL) {
		  if(strcmp(ent->d_name,".") && strcmp(ent->d_name,"..")) {
			  
				printf ("%s\n", ent->d_name);
				tmp[count++] = std::string(ent->d_name);
			  }
		  
	  }
	  closedir (dir);
	} else {
	  /* could not open directory */
	  perror ("");
  
	}
	tmp[count++] = std::string("new_map");
	
	rblocks = new EntityManager();
	
	strings = new sf::String[count];
	maps = new std::string[count];
	
	for(int i=0;i<count;i++) {
		maps[i] = tmp[i];
		strings[i] = sf::String(maps[i]);
		strings[i].SetColor(sf::Color::Black);
	}

	int tile_number = sqrt((float)count) + 1;
	for(int i=0;i<tile_number;i++) {
		for(int j=0;j<tile_number;j++) {
			if(i*tile_number + j >= count) break;
			
			sf::Shape tmp;
		
													

			tmp.AddPoint(sf::Vector2<float>(j*(resource::consts::SCREEN_WIDTH/tile_number),
										    i*(resource::consts::SCREEN_HEIGHT/tile_number)));
			tmp.AddPoint(sf::Vector2<float>((j+1)*(resource::consts::SCREEN_WIDTH/tile_number),
										    (i)*(resource::consts::SCREEN_HEIGHT/tile_number)));
			tmp.AddPoint(sf::Vector2<float>(j*resource::consts::SCREEN_WIDTH/tile_number,
											(i+1)*(resource::consts::SCREEN_HEIGHT/tile_number)));
			tmp.AddPoint(sf::Vector2<float>((j+1)*(resource::consts::SCREEN_WIDTH/tile_number),
											  (i+1)*(resource::consts::SCREEN_HEIGHT/tile_number)));
			rblocks->PushBack(new RectangleBlock(tmp,
											resource::function::GetSpriteID("BOX_TEXTURE"),
											 resource::globalTexture->instance()->GetTextureManager(),false));
			
			
			while(strings[i*tile_number+j].GetRect().GetWidth() >= resource::consts::SCREEN_WIDTH/tile_number-10) {
				int prev_size = (strings[i*tile_number+j].GetSize());
				strings[i*tile_number+j].SetSize(--prev_size);
			}
			strings[i*tile_number+j].SetPosition(tmp.GetPointPosition(0) + 
				sf::Vector2<float>((resource::consts::SCREEN_WIDTH/tile_number - strings[i*tile_number+j].GetRect().GetWidth())*1/2 +5,
									(resource::consts::SCREEN_HEIGHT/tile_number - strings[i*tile_number+j].GetRect().GetHeight())*1/2));
		
		
		}
	}

	

	

}

Menu::~Menu() {
	delete[] maps;
//	delete[] rblocks;
}


std::string Menu::Loop() {
	sf::Event my_event;
	bool running = true;
	std::string ret;
	while(running) {
	while(target->GetEvent(my_event)) {
		switch(my_event.Type) {
		case sf::Event::KeyPressed: 
			
			break;
		case sf::Event::MouseButtonReleased:
			if(my_event.MouseButtonReleased == 9) {
				ret = CheckIntersection(sf::Vector2<float>(my_event.MouseButton.X,my_event.MouseButton.Y));
				if(ret != "") {
					
					
					target->GetEvent(my_event);
					return ret;
				}
			}
			break;
		}
	}
	Update();
	Render();
	target->Display();
	}
	
}

void Menu::Update() {

}

void Menu::Render() {
	
	
	target->Clear();
	int i=0;
	for(EntityManagerTypes::iterator it = rblocks->begin();it != rblocks->end();it++) {
		(*it)->Render(target,resource::globalTexture->instance()->GetTextureManager(),sf::Vector2<float>(0,0));
		
		
		
	}
	for(int i=0;i<count;i++) {
		target->Draw(strings[i]);
	}
}

std::string Menu::CheckIntersection(sf::Vector2<float> p) {
	int i = 0;
	for(EntityManagerTypes::iterator it = rblocks->begin();it != rblocks->end() ;it++) {
		if(dynamic_cast<RectangleBlock*>(*it)->PointIntersect(p) == true) {
			return map_dir_path + maps[i];
		}
		i++;
	}
	return "";
}