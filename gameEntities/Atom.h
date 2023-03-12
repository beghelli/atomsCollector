#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include "GameEntity.h"
#include "ScreenWriter.h"

using namespace Engine;
using namespace Support;

namespace GameEntities
{

	class Atom : public GameEntity
	{
		public:
			Atom(int x, int y);

			void update(const unsigned char* keys, SDL_Point mousePosition, bool isMouseDown);
			bool shouldDestroy();
			bool isGameOver();
			bool processCollisions(vector<GameEntity*> collidingEntities);
			void render(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter);
			vector<GameEntity*> getNewGameEntities();

		private:
			int originalX;
			int originalY;
	};

}
