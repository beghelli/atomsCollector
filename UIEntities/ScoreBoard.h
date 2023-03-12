#pragma once
#include <SDL2/SDL.h>
#include "Entity.h"

using namespace Engine;

namespace UIEntities
{
	class ScoreBoard : public Entity
	{
		public:
			void update(const unsigned char* keys, SDL_Point mousePosition, bool isMouseDown);
			void render(SDL_Renderer* renderer, SDL_Texture* textures[]);
	};
}
