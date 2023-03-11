#pragma once
#include <vector>
#include "GameEntity.h"
#include "EntityRepository.h"

using namespace Support;

namespace Support
{

	class CollisionDetector
	{
		private:
			EntityRepository* entityRepository;

		public:
			CollisionDetector(EntityRepository* entityRepository);
			vector<GameEntity*> getCollidingEntities(GameEntity* gameEntity);
	};

}
