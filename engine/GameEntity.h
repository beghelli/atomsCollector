#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "Entity.h"

using namespace std;

namespace Engine 
{
	class GameEntity : public Entity
	{

		protected:
			float xv;
			float yv;
			double zAngle;
			double acceleration;
			bool isAcceleratingX;
			bool isAcceleratingY;
			int currentMaxVelocity;
			int baseMaxVelocity;

			struct
			{
				bool isOnLimitLeftX;
				bool isOnLimitRightX;
				bool isOnLimitTopY;
				bool isOnLimitBottomY;
			} limitPositionState;

			void updateScreenLimitPositionState();
			void limitPositionToScreenSize();
			bool reachedAnyScreenLimit();

		public:
			void increaseAccelerationIn(double increaseValue);
			void setZAngle(double angle);
			
			virtual bool isGameOver()=0;
			virtual bool processCollisions(vector<GameEntity*> collidingEntities)=0;
			virtual vector<GameEntity*> getNewGameEntities()=0;
	};
}
