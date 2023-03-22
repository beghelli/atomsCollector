#pragma once
#include <SDL2/SDL.h>
#include "EntityRepository.h"
#include "ScreenWriter.h"
#include "Entity.h"
#include "GameEntity.h"

using namespace Support;
using namespace Engine;

namespace Engine
{
	class GameScene
	{
		public:
			virtual int load(EntityRepository<GameEntity>* entityRepository, EntityRepository<Entity>* UIEntityRepository)=0;
			virtual void onGameLoopStart(EntityRepository<GameEntity>* entityRepository, EntityRepository<Entity>* UIEntityRepository, ScreenWriter* screenWriter, const unsigned char* keys, bool isMouseDown)=0;
	};
}
