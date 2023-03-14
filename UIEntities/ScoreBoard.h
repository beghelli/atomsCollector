#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "Entity.h"
#include "Message.h"

using namespace Engine;
using namespace Support;

namespace UIEntities
{
	class ScoreBoard : public Entity
	{
		private:
			int otherAtomsQuantity;
			string label;
			int maxCapacity;
			int atomicNumber;
			SDL_Color color;

		public:
			ScoreBoard(string label);
			ScoreBoard(string label, int maxCapacity, int atomicNumber, SDL_Color color, int x, int y);
			bool load(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter);
			void update(const unsigned char* keys, SDL_Point mousePosition, bool isMouseDown);
			void render(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter);
			void registerPlayerAtomCollisionListener();
	};
}
