#pragma once
#include <functional>
#include <unordered_map>
#include <string>

using namespace std;

namespace Engine
{
	namespace Support
	{
		template <class C> class EntityRepository
		{
			private:
				unordered_map<unsigned int, C*> gameEntitiesMap;	
				unordered_map<string, unordered_map<string, int>> entitiesMapCount;
				unsigned int entitiesCount;
				unsigned int nextEntityId;
				void initCount(string classType, string instanceType);
				void changeEntitiesMapCount(string classType, string instanceType, int changeValue);

			public:
				EntityRepository();
				~EntityRepository();
				void addEntity(C* gameEntity);
				void deleteEntity(unsigned int gameEntityId);
				void iterate(function<bool(unsigned int, C*)> iteratorFunc);
				void clear();
				int getEntityCount(string classType, string instanceType);
		};
	}
}
