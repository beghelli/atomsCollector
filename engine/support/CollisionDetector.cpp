#include <iostream>
#include <vector>
#include "constants.h"
#include "CollisionDetector.h"
#include "EntityRepository.h"
#include "GameEntity.h"

using namespace Engine;

Support::CollisionDetector::CollisionDetector(EntityRepository<GameEntity>* entityRepository)
{
	this->entityRepository = entityRepository;
}

vector<GameEntity*> Support::CollisionDetector::getCollidingEntities(GameEntity* gameEntity)
{
	vector<GameEntity*> collidingEntities;
	struct EntityLimits
	{
		int top;
		int bottom;
		int left;
		int right;
	};

	EntityLimits mainEntityLimits; 
	mainEntityLimits.top = gameEntity->getY();
	mainEntityLimits.bottom = gameEntity->getY() + gameEntity->getHeight();
	mainEntityLimits.left = gameEntity->getX();
	mainEntityLimits.right = gameEntity->getX() + gameEntity->getWidth();

	auto checkOtherEntityForCollisions = [&](unsigned int id, GameEntity* iteratedGameEntity) -> bool 
	{
		bool isCollidingX = false;
		bool isCollidingY = false;

		if (gameEntity->getId() == id)
		{
			return true;
		}

		EntityLimits iteratedEntityLimits;
		iteratedEntityLimits.top = iteratedGameEntity->getY();
		iteratedEntityLimits.bottom = iteratedGameEntity->getY() + iteratedGameEntity->getHeight();
		iteratedEntityLimits.left = iteratedGameEntity->getX();
		iteratedEntityLimits.right = iteratedGameEntity->getX() + iteratedGameEntity->getWidth();

		// Check X
		isCollidingY = (mainEntityLimits.top >= iteratedEntityLimits.top
				&& mainEntityLimits.top <= iteratedEntityLimits.bottom)
			|| (iteratedEntityLimits.top >= mainEntityLimits.top
				&& iteratedEntityLimits.top <= mainEntityLimits.bottom);
		
		if (! isCollidingY)
		{
			isCollidingY = (mainEntityLimits.bottom <= iteratedEntityLimits.bottom
					&& mainEntityLimits.bottom >= iteratedEntityLimits.top)
				|| (iteratedEntityLimits.bottom <= mainEntityLimits.bottom
					&& iteratedEntityLimits.bottom >= mainEntityLimits.top);
		}

		// Check Y
		isCollidingX = (mainEntityLimits.left >= iteratedEntityLimits.left
				&& mainEntityLimits.left <= iteratedEntityLimits.right)
			|| (iteratedEntityLimits.left >= mainEntityLimits.left
				&& iteratedEntityLimits.left <= mainEntityLimits.right);

		if (! isCollidingX)
		{
			isCollidingX = (mainEntityLimits.right <= iteratedEntityLimits.right
					&& mainEntityLimits.right >= iteratedEntityLimits.left)
				|| (iteratedEntityLimits.right <= mainEntityLimits.right
					& iteratedEntityLimits.right >= mainEntityLimits.left);
		}

		if (DEBUG)
		{
			cout << "--- Collision Calculated ---" << endl;
			cout << "Is Colliding X - " << isCollidingX << endl;
			cout << "Is Colliding Y - " << isCollidingY << endl;
			cout << "Main entity ID " << gameEntity->getId() << endl;
			cout << "Top: " << mainEntityLimits.top 
				<< " Bottom: " << mainEntityLimits.bottom
				<< " Left: " << mainEntityLimits.left
				<< " Right: " << mainEntityLimits.right
				<< endl;
			cout << "Other entity ID " << iteratedGameEntity->getId() << endl;
			cout << "Top: " << iteratedEntityLimits.top 
				<< " Bottom: " << iteratedEntityLimits.bottom
				<< " Left: " << iteratedEntityLimits.left
				<< " Right: " << iteratedEntityLimits.right
				<< endl;
		}

		if (isCollidingX && isCollidingY)
		{	
			collidingEntities.push_back(iteratedGameEntity);
		}
		
		return true;
	};

	entityRepository->iterate(checkOtherEntityForCollisions);

	return collidingEntities;
}
