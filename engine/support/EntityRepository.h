#pragma once
#include <functional>
#include <unordered_map>
#include <string>
#include "GameEntity.h"

using namespace std;
using namespace Engine;

namespace Support
{
	class EntityRepository
	{
		private:
			unordered_map<unsigned int, GameEntity*> gameEntitiesMap;	
			unsigned int entitiesCount;
			unsigned int nextEntityId;

		public:
			EntityRepository();
			~EntityRepository();
			void addEntity(GameEntity* gameEntity);
			void deleteEntity(unsigned int gameEntityId);
			void iterate(function<bool(unsigned int, GameEntity*)> iteratorFunc);
			void clear();
	};
}
