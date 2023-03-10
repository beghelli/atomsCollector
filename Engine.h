#pragma once
#include <SDL2/SDL.h>
#include "Engine.h"
#include "Game.h"
#include "GameEntityRepository.h"
#include "CollisionDetector.h"
#include "ScreenWriter.h"

#define MAX_ENTITIES 100

using namespace Support;

class Engine
{
	public:
		Engine(Game* game);
		int run();

	private:
		SDL_Window* window;
		SDL_Renderer* renderer;

		SDL_Point mousePosition;
		SDL_Texture *textures[MAX_ENTITIES] = { nullptr };
		GameEntityRepository* entityRepository;
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
