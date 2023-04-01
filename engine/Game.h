#pragma once
#include <functional>
#include <vector>
#include <SDL2/SDL.h>
#include "EntityRepository.h"
#include "ScreenWriter.h"
#include "Entity.h"
#include "GameEntity.h"
#include "GameScene.h"

using namespace Engine;
using namespace Engine::Support;

namespace Engine
{
	class Game
	{
		public:
			static const int STATUS_OUT_GAME = 1;
			static const int STATUS_IN_GAME = 2;
			static const int STATUS_LOADING = 3;

			int status;
			GameScene* currentGameScene;
			vector<function<void(EntityRepository<GameEntity>* entityRepository, EntityRepository<Entity>* UIEntityRepository)>> loadingQueue;
			
			virtual bool load(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter)=0;
			bool loadScene(GameScene* gameScene);
			virtual bool renderMenus(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter, const unsigned char* keys, bool isMouseDown)=0; 
			virtual void renderLoadingScreen(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter, const unsigned char* keys, bool isMouseDown)=0;

	};
}
