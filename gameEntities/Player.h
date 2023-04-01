#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include "GameEntity.h"
#include "ScreenWriter.h"

using namespace std;
using namespace Engine;
using namespace Engine::Support;

namespace GameEntities
{
	class Player : public GameEntity
	{

		private:
			int life;
			bool isRunning;
			void calculatePosition(const unsigned char* keys);
			void calculateZAngle(SDL_Point mousePosition);
			float getCurrentMovingSpeed();
			void fire(bool isMouseDown);

		public:
			Player(int x, int y);

			void setLife(int life);
			int getLife();
			void update(const unsigned char* keys, SDL_Point mousePosition, bool isMouseDown);
			bool shouldDestroy();
			bool isGameOver();
			bool processCollisions(vector<GameEntity*> collidingEntities);
			void render(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter);
			vector<GameEntity*> getNewGameEntities();
	};
}
