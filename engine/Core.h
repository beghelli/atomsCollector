#pragma once
#include <SDL2/SDL.h>
#include "Game.h"
#include "Entity.h"
#include "GameEntity.h"
#include "EntityRepository.h"
#include "CollisionDetector.h"
#include "ScreenWriter.h"

#define MAX_ENTITIES 100

using namespace Engine::Support;

namespace Engine 
{
	class Core
	{
		
		public:
			Core(Game* game);
			int run();
			static void runGameLoaders(Core* core);

			EntityRepository<GameEntity>* entityRepository;
			EntityRepository<Entity>* UIEntityRepository;

		private:
			SDL_Window* window;
			SDL_Renderer* renderer;

			SDL_Point mousePosition;
			SDL_Texture *textures[MAX_ENTITIES] = { nullptr };
			CollisionDetector* collisionDetector;
			ScreenWriter* screenWriter;
			Game* game;
			bool isGameOver;

			bool init();
			bool load();
			void unload();
			void kill();
			bool loop();
			bool gameLoop(const unsigned char* keys, bool isMouseDown);

	};
}
