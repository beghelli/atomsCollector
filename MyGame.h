#pragma once
#include <SDL2/SDL.h>
#include "EntityRepository.h"
#include "ScreenWriter.h"
#include "Entity.h"
#include "GameEntity.h"
#include "Game.h"

using namespace Engine::Support;
using namespace Engine;

class MyGame: public Game
{
	public:
		bool load(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter);
		bool renderMenus(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter, const unsigned char* keys, bool isMouseDown); 
		void renderLoadingScreen(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter, const unsigned char* keys, bool isMouseDown);
};
