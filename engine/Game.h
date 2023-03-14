#pragma once
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
		virtual bool load(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter)=0;
		virtual void setGameScene(EntityRepository<GameEntity>* entityRepository, EntityRepository<Entity>* UIEntityRepository)=0;
		virtual void onGameLoopStart(EntityRepository<GameEntity>* entityRepository, EntityRepository<Entity>* UIEntityRepository)=0;

};
