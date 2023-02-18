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

			bool hasCollidingCoordinates(GameEntity* mainEntity, GameEntity* otherEntity);
			vector<vector<int>> incrementEntityCoord(vector<vector<int>> bodyCoord, int incrementValue);
			bool isValueInsideCoord(int value, vector<vector<int>>bodyCoord);
			bool hasOneValueInCommon(vector<vector<int>> bodyCoord, vector<vector<int>> otherBodyCoord);
		public:
			CollisionDetector(GameEntityRepository* entityRepository);
			vector<GameEntity*> getCollidingEntities(GameEntity* gameEntity);
	};

}
