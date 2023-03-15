#pragma once
#include "GameScene.h"
#include <SDL2/SDL.h>
#include "EntityRepository.h"
#include "ScreenWriter.h"
#include "Entity.h"
#include "GameEntity.h"

namespace Scenes
{
	class HuntAtoms : public GameScene
	{
		public:
			int load(EntityRepository<GameEntity>* entityRepository, EntityRepository<Entity>* UIEntityRepository);
			void onGameLoopStart(EntityRepository<GameEntity>* entityRepository, EntityRepository<Entity>* UIEntityRepository);

		private:
			void fillAtoms(EntityRepository<GameEntity>* entityRepository);
			void addUIElements(EntityRepository<Entity>* UIEntityRepository);
	};
}
