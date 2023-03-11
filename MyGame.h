#pragma once
#include <SDL2/SDL.h>
#include "EntityRepository.h"
#include "Game.h"

using namespace Support;

class MyGame: public Game
{
	public:
		bool load(SDL_Renderer* renderer, SDL_Texture* textures[]);
		void setGameScene(EntityRepository* entityRepository);

	private:
		void fillAtoms(EntityRepository* entityRepository);

};
