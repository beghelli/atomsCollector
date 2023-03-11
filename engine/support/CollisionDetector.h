#pragma once
#include <vector>
#include "GameEntity.h"
#include "GameEntityRepository.h"

using namespace Support;

namespace Support
{

	class CollisionDetector
	{
		private:
			GameEntityRepository* entityRepository;

		public:
			CollisionDetector(GameEntityRepository* entityRepository);
			vector<GameEntity*> getCollidingEntities(GameEntity* gameEntity);
	};

}
