#pragma once
#include <SDL2/SDL.h>
#include "Game.h"
#include "EntityRepository.h"
#include "CollisionDetector.h"
#include "ScreenWriter.h"

#define MAX_ENTITIES 100

using namespace Support;

namespace Engine 
{

	class Core
	{
		public:
			Core(Game* game);
			int run();

		private:
			SDL_Window* window;
			SDL_Renderer* renderer;

			SDL_Point mousePosition;
			SDL_Texture *textures[MAX_ENTITIES] = { nullptr };
			EntityRepository* entityRepository;
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
			bool menuLoop(const unsigned char* keys, bool isMouseDown);

	};
}
