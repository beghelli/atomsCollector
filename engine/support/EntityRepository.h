#pragma once
#include <functional>
#include <unordered_map>
#include <string>

using namespace std;

namespace Support
{
	template <class C> class EntityRepository
	{
		private:
			unordered_map<unsigned int, C*> gameEntitiesMap;	
			unsigned int entitiesCount;
			unsigned int nextEntityId;

		public:
			EntityRepository();
			~EntityRepository();
			void addEntity(C* gameEntity);
			void deleteEntity(unsigned int gameEntityId);
			void iterate(function<bool(unsigned int, C*)> iteratorFunc);
			void clear();
	};
}
