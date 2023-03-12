#pragma once
#include <SDL2/SDL.h>
#include "EntityRepository.h"
#include "ScreenWriter.h"
#include "Entity.h"
#include "GameEntity.h"
#include "Game.h"

using namespace Support;
using namespace Engine;

class MyGame: public Game
{
	public:
		bool load(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter);
		void setGameScene(EntityRepository<GameEntity>* entityRepository, EntityRepository<Entity>* UIEntityRepository);

	private:
		void fillAtoms(EntityRepository<GameEntity>* entityRepository);
		void addUIElements(EntityRepository<Entity>* UIEntityRepository);

};
