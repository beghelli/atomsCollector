#include <functional>
#include <iostream>
#include <unordered_map>
#include "EntityRepository.h"
#include "GameEntity.h"
#include "Entity.h"

using namespace std;
using namespace Engine;

template <class C> Support::EntityRepository<C>::EntityRepository()
{
	this->entitiesCount = 0;
	this->nextEntityId = 1;
}

template <class C> Support::EntityRepository<C>::~EntityRepository()
{
	clear();
}

template <class C> void Support::EntityRepository<C>::addEntity(C* gameEntity)
{
	gameEntity->setId(this->nextEntityId);
	this->gameEntitiesMap[this->nextEntityId++] = gameEntity;
	this->entitiesCount++;
}

template <class C> void Support::EntityRepository<C>::deleteEntity(unsigned int gameEntityId)
{
	delete this->gameEntitiesMap[gameEntityId];
	this->gameEntitiesMap.erase(gameEntityId);
	this->entitiesCount--;
}

template <class C> void Support::EntityRepository<C>::iterate(function<bool(unsigned int, C*)> iteratorFunc)
{
	for (auto gameEntityPair : this->gameEntitiesMap)
	{
		bool keepEntity = iteratorFunc(gameEntityPair.first, gameEntityPair.second);
		if (! keepEntity)
		{
			deleteEntity(gameEntityPair.first);
		}
	}
}

template <class C> void Support::EntityRepository<C>::clear()
{
	iterate([](unsigned int id, C* gameEntity) -> bool { return false; });
}

template class Support::EntityRepository<GameEntity>;
template class Support::EntityRepository<Entity>;
