#pragma once
#include "GameScene.h"
#include <SDL2/SDL.h>
#include "EntityRepository.h"
#include "ScreenWriter.h"
#include "Entity.h"
#include "GameEntity.h"
#include "AtomGenerator.h"
#include "LevelDAO.h"

using namespace Data;
using namespace Scenes::Support;

namespace Scenes
{
	class HuntAtoms : public GameScene
	{
		public:
			HuntAtoms(LevelData levelData);
			int load(EntityRepository<GameEntity>* entityRepository, EntityRepository<Entity>* UIEntityRepository);
			void onGameLoopStart(EntityRepository<GameEntity>* entityRepository, EntityRepository<Entity>* UIEntityRepository, ScreenWriter* screenWriter, const unsigned char* keys, bool isMouseDown);

		private:
			AtomGenerator* atomGenerator;
			LevelData levelData;
			void addUIElements(EntityRepository<Entity>* UIEntityRepository);
	};
}
