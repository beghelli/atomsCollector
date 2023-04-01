#include <functional>
#include <iostream>
#include <unordered_map>
#include "EntityRepository.h"
#include "GameEntity.h"
#include "Entity.h"

using namespace std;
using namespace Engine;

template <class C> Engine::Support::EntityRepository<C>::EntityRepository()
{
	this->entitiesCount = 0;
	this->nextEntityId = 1;
}

template <class C> Engine::Support::EntityRepository<C>::~EntityRepository()
{
	clear();
}

template <class C> void Engine::Support::EntityRepository<C>::addEntity(C* gameEntity)
{
	gameEntity->setId(this->nextEntityId);
	this->gameEntitiesMap[this->nextEntityId++] = gameEntity;
	this->entitiesCount++;
	this->changeEntitiesMapCount(gameEntity->getClassType(), gameEntity->getInstanceType(), 1);
}

template <class C> void Engine::Support::EntityRepository<C>::deleteEntity(unsigned int gameEntityId)
{
	auto entity = this->gameEntitiesMap[gameEntityId];
	this->changeEntitiesMapCount(entity->getClassType(), entity->getInstanceType(), -1);
	delete this->gameEntitiesMap[gameEntityId];
	this->gameEntitiesMap.erase(gameEntityId);
	this->entitiesCount--;
}

template <class C> void Engine::Support::EntityRepository<C>::iterate(function<bool(unsigned int, C*)> iteratorFunc)
{
	auto workingGameEntitiesMap = this->gameEntitiesMap;
	for (auto gameEntityPair : workingGameEntitiesMap)
	{
		bool keepEntity = iteratorFunc(gameEntityPair.first, gameEntityPair.second);
		if (! keepEntity)
		{
			deleteEntity(gameEntityPair.first);
		}
	}
}

template <class C> void Engine::Support::EntityRepository<C>::clear()
{
	iterate([](unsigned int id, C* gameEntity) -> bool { return false; });
}

template <class C> void Engine::Support::EntityRepository<C>::changeEntitiesMapCount(string classType, string instanceType, int changeValue)
{
	this->initCount(classType, instanceType);
	this->entitiesMapCount[classType][instanceType] += changeValue;
}

template <class C> int Engine::Support::EntityRepository<C>::getEntityCount(string classType, string instanceType)
{
	this->initCount(classType, instanceType);
	return this->entitiesMapCount[classType][instanceType];
}

template <class C> void Engine::Support::EntityRepository<C>::initCount(string classType, string instanceType)
{
	if (! this->entitiesMapCount.count(classType))
	{
		unordered_map<string, int> instanceTypeCount;
		this->entitiesMapCount[classType] = instanceTypeCount;
	}

	if (! this->entitiesMapCount[classType].count(instanceType))
	{
		this->entitiesMapCount[classType][instanceType] = 0;
	}
}

template class Engine::Support::EntityRepository<GameEntity>;
template class Engine::Support::EntityRepository<Entity>;
