#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <SDL2/SDL.h>
#include "GameEntity.h"
#include "ScreenWriter.h"
#include "AtomDAO.h"

using namespace Data;
using namespace Engine;
using namespace Engine::Support;

namespace GameEntities
{

	class Atom : public GameEntity
	{
		public:
			AtomData atomData;

			Atom(int x, int y, AtomData atomData);

			bool load(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter);
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
