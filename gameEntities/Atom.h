#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include "GameEntity.h"

using namespace GameEntities;

namespace GameEntities
{

	class Atom : public GameEntity
	{
		public:
			Atom(int x, int y);

			void update(const unsigned char* keys, SDL_Point mousePosition, bool isMouseDown);
			bool shouldDestroy();
			bool processCollisions(vector<GameEntity*> collidingEntities);
			void render(SDL_Renderer* renderer, SDL_Texture* textures[]);
			vector<GameEntity*> getNewGameEntities();
		private:
			int originalX;
			int originalY;
	};

}
