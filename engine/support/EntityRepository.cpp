#include <functional>
#include <iostream>
#include <unordered_map>
#include "EntityRepository.h"
#include "GameEntity.h"

using namespace std;
using namespace Engine;

Support::EntityRepository::EntityRepository()
{
	this->entitiesCount = 0;
	this->nextEntityId = 1;
}

Support::EntityRepository::~EntityRepository()
{
	clear();
}

void Support::EntityRepository::addEntity(GameEntity* gameEntity)
{
	gameEntity->setId(this->nextEntityId);
	this->gameEntitiesMap[this->nextEntityId++] = gameEntity;
	this->entitiesCount++;
}

void Support::EntityRepository::deleteEntity(unsigned int gameEntityId)
{
	delete this->gameEntitiesMap[gameEntityId];
	this->gameEntitiesMap.erase(gameEntityId);
	this->entitiesCount--;
}

void Support::EntityRepository::iterate(function<bool(unsigned int, GameEntity*)> iteratorFunc)
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

void Support::EntityRepository::clear()
{
	iterate([](unsigned int id, GameEntity* gameEntity) -> bool { return false; });
}
