#pragma once
#include <functional>
#include <vector>
#include <SDL2/SDL.h>
#include "EntityRepository.h"
#include "ScreenWriter.h"
#include "Entity.h"
#include "GameEntity.h"

using namespace Engine;
using namespace Support;

class Game
{
	public:
		static const int STATUS_IN_MENU = 1;
		static const int STATUS_IN_GAME = 2;
		static const int STATUS_LOADING = 3;

		int status;
		vector<function<void(EntityRepository<GameEntity>* entityRepository, EntityRepository<Entity>* UIEntityRepository)>> loadingQueue;
		
		virtual bool load(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter)=0;
		virtual bool renderMenus(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter, const unsigned char* keys, bool isMouseDown)=0; 
		virtual void renderLoadingScreen(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter, const unsigned char* keys, bool isMouseDown)=0;
		virtual void onGameLoopStart(EntityRepository<GameEntity>* entityRepository, EntityRepository<Entity>* UIEntityRepository)=0;

};
