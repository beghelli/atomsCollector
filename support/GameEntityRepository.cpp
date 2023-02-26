#include <functional>
#include <iostream>
#include <unordered_map>
#include "GameEntityRepository.h"
#include "GameEntity.h"

using namespace std;
using namespace GameEntities;

Support::GameEntityRepository::GameEntityRepository()
{
	this->entitiesCount = 0;
	this->nextEntityId = 1;
}

Support::GameEntityRepository::~GameEntityRepository()
{
	clear();
}

void Support::GameEntityRepository::addEntity(GameEntity* gameEntity)
{
	gameEntity->setId(this->nextEntityId);
	this->gameEntitiesMap[this->nextEntityId++] = gameEntity;
	this->entitiesCount++;
}

void Support::GameEntityRepository::deleteEntity(unsigned int gameEntityId)
{
	delete this->gameEntitiesMap[gameEntityId];
	this->gameEntitiesMap.erase(gameEntityId);
	this->entitiesCount--;
}

void Support::GameEntityRepository::iterate(function<bool(unsigned int, GameEntity*)> iteratorFunc)
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

void Support::GameEntityRepository::clear()
{
	iterate([](unsigned int id, GameEntity* gameEntity) -> bool { return false; });
}
