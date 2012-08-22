#include "SaveToEngine.h"
#include "resource.h"
#include "dirent.h"
SaveToEngine::SaveToEngine(std::string output,Map* map):
_map(map),
mapname(output){

}


SaveToEngine::~SaveToEngine() {

}

void SaveToEngine::SaveStart() {
//	resource::objects::GlobalTextManager.instance()->GetFontManager()->Add(new Font("Saved",3));
	DIR *dir;
	struct dirent *ent;
	dir = opendir (resource::consts::map_dir_path.c_str());
		std::string tmp[50];
	int max_number = 0;
	const char*	tmp_pointer;
	if (dir != NULL) {

	  /* print all the files and directories within directory */
	  while ((ent = readdir (dir)) != NULL) {
		  if(strcmp(ent->d_name,".") && strcmp(ent->d_name,"..")) {
			  tmp_pointer = strstr(mapname.c_str(),"new_map");
			 
				  if(tmp_pointer != NULL) {
					  if(strcmp(tmp_pointer,"new_map") == 0){
					  tmp_pointer =strstr(ent->d_name,tmp_pointer);
					  if(tmp_pointer != NULL){
					  
						  tmp_pointer += strlen("new_map");
						  int number = atoi(tmp_pointer);
						  if(number > max_number) max_number = number;
					
					  }
				  }
			  }
		  }
	  }

						 stringstream os;
						 os << resource::consts::map_dir_path << "new_map" << ++max_number;
					  mapname = std::string(os.str());
	  closedir (dir);
	} else {
	  /* could not open directory */
	  perror ("");
  
	}

	file.open(mapname);
	for(EntityManagerTypes::iterator it = _map->blocks->begin();
		it != _map->blocks->end();
		it++) {
			stringstream os;
			os << (*it)->SerializeForEngine() << endl;
			file << os.str();
	}
	file.close();
}