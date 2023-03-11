#pragma once
#include <SDL2/SDL.h>
#include "GameEntityRepository.h"

using namespace Support;

class Game
{

	public:
		virtual bool load(SDL_Renderer* renderer, SDL_Texture* textures[])=0;
		virtual void setGameScene(GameEntityRepository* entityRepository)=0;

};
