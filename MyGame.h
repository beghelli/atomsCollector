#pragma once
#include <SDL2/SDL.h>
#include "GameEntityRepository.h"
#include "Game.h"

using namespace Support;

class MyGame: public Game
{
	public:
		bool load(SDL_Renderer* renderer, SDL_Texture* textures[]);
		void setGameScene(GameEntityRepository* entityRepository);

	private:
		void fillAtoms(GameEntityRepository* entityRepository);

};
