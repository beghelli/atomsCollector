#pragma once
#include <SDL2/SDL.h>
#include "EntityRepository.h"

using namespace Support;

class Game
{

	public:
		virtual bool load(SDL_Renderer* renderer, SDL_Texture* textures[])=0;
		virtual void setGameScene(EntityRepository* entityRepository)=0;

};
