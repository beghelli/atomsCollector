#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "GameEntity.h"

using namespace std;

namespace GameEntities
{
	class GameEntity
	{

	protected:
		unsigned int id;
		int x;
		int y;
		float xv;
		float yv;
		double zAngle;
		double acceleration;
		bool isAcceleratingX;
		bool isAcceleratingY;
		int currentMaxVelocity;
		int baseMaxVelocity;

		int entityHeight;
		int entityWidth;
		string entityTextureFile;
		int entityTextureIndex;
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
		void setId(unsigned int id);
		unsigned int getId();
		int getX();
		int getY();
		int getHeight();
		int getWidth();
		void increaseAccelerationIn(double increaseValue);
		void setZAngle(double angle);
		bool load(SDL_Renderer* renderer, SDL_Texture* textures[]);
		void destroy(SDL_Texture* textures[]);

		string type;

		virtual void update(const unsigned char* keys, SDL_Point mousePosition, bool isMouseDown)=0;
		virtual bool shouldDestroy()=0;
		virtual bool isGameOver()=0;
		virtual bool processCollisions(vector<GameEntity*> collidingEntities)=0;
		virtual void render(SDL_Renderer* renderer, SDL_Texture* textures[])=0;
		virtual vector<GameEntity*> getNewGameEntities()=0;
	};
}
