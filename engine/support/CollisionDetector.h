#pragma once
#include <vector>
#include "GameEntity.h"
#include "EntityRepository.h"

using namespace Support;
using namespace Engine;

namespace Support
{

	class CollisionDetector
	{
		private:
			EntityRepository<GameEntity>* entityRepository;

		public:
			CollisionDetector(EntityRepository<GameEntity>* entityRepository);
			vector<GameEntity*> getCollidingEntities(GameEntity* gameEntity);
	};

}
