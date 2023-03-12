#pragma once
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

		public:
			bool load(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter);
			void update(const unsigned char* keys, SDL_Point mousePosition, bool isMouseDown);
			void render(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter);
	};
}
