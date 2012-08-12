#ifndef INC_ENTITYMANAGER_H
#define INC_ENTITYMANAGER_H

#include "Entity.h"
#include <set>
#include <list>
#include "resource.h"
/*
struct Comparator
{
	bool operator() (const Entity* a,const Entity* b) {
		if(a->x < b.x ) return true;
		if(a.x == b.x) {
			if(a.y < b.y) {
				return true;
			} else {
				return false;
			}
		}
		return false;
	}
} comp;
*/

namespace EntityManagerTypes {
	typedef std::list<Entity*>::iterator iterator;
	class EntityManager {
	private:
		std::list<Entity*>	entities;
		int					id_count;
	public:
		

		EntityManager();
		~EntityManager();
	
		void				Push(Entity* entity);
		void				PushBack(Entity* entity);
		Entity*				Get(Entity* entity);
		void				Remove(Entity* entity);
		void				Remove(EntityManagerTypes::iterator);
		void				Sort();
		
		//inline std::vector<Entity*> GetEntities() const {return entities;}
		inline				int GetIDcount() const {return id_count;}
		inline				int	GetSize()	 const {return entities.size();}

		inline				iterator begin() {return entities.begin();}
		inline				iterator end()	{return entities.end();}

	};  
}


#endif