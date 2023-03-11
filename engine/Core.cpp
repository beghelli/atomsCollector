#include <iostream>
#include <SDL2/SDL.h>
#include "Core.h"
#include "Game.h"
#include "constants.h"
#include "GameEntityRepository.h"
#include "CollisionDetector.h"
#include "ScreenWriter.h"
#include "Message.h"

using namespace Support;

Engine::Core::Core(Game* game)
{
	this->game = game;
}

int Engine::Core::run()
{
	if (init() && load() && game->load(renderer, textures))
	{
		while (loop())
		{
			SDL_Delay(10);
		}
	}

	kill();
	return 0;
}

bool Engine::Core::loop()
{
	const unsigned char* keys = SDL_GetKeyboardState( NULL );
	bool isMouseDown = false;
	SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
	SDL_Event e;
	
	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
			case SDL_QUIT:
				return false;
			case SDL_MOUSEBUTTONDOWN:
				isMouseDown = true;
				break;
			case SDL_MOUSEBUTTONUP:
				isMouseDown = false;
				break;
		}
	}

	if (isGameOver)
	{
		return menuLoop(keys, isMouseDown);
	}
	else
	{
		return gameLoop(keys, isMouseDown);
	}

	return false;
}

bool Engine::Core::menuLoop(const unsigned char* keys, bool isMouseDown)
{
	SDL_SetRenderDrawColor(renderer, 50, 50, 255, 255);
	SDL_RenderClear(renderer);
	
	Message message("Pressione N para comecar!", 25, 1, 150, 150, 500, 100);
	screenWriter->write(message);

	SDL_RenderPresent(renderer);

	if (keys[SDL_SCANCODE_N])
	{
		isGameOver = false;
		game->setGameScene(entityRepository);
	}

	return true;
}

bool Engine::Core::gameLoop(const unsigned char* keys, bool isMouseDown)
{	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	auto processEntitiesPosition = [&](unsigned int id, GameEntity* gameEntity) -> bool
	{
		gameEntity->update(keys, mousePosition, isMouseDown);
		return true;
	};
	entityRepository->iterate(processEntitiesPosition);

	vector<GameEntity*> entitiesToBeDeleted;
	auto processCollisions = [&](unsigned int id, GameEntity* gameEntity) -> bool
	{
		if (DEBUG)
		{
			cout << "###### Processing collisions for entity ID " << gameEntity->getId() << " #####" << endl;
		}
		vector<GameEntity*> collidingEntities = collisionDetector->getCollidingEntities(gameEntity);
		bool shouldKeep = gameEntity->processCollisions(collidingEntities);
		if (! shouldKeep)
		{
			entitiesToBeDeleted.push_back(gameEntity);
		}

		return true;
	};
	entityRepository->iterate(processCollisions);
	for (GameEntity* gameEntity : entitiesToBeDeleted)
	{
		entityRepository->deleteEntity(gameEntity->getId()); // Not ideal, forces a lookup in the entities array when we can just pass the entity to the repository already.
	}

	auto renderEntities = [&](unsigned int id, GameEntity* gameEntity) -> bool
	{
		if (isGameOver)
		{
			return false;
		}

		isGameOver = gameEntity->isGameOver();
		if (gameEntity->shouldDestroy())
		{
			return false;
		}
		else
		{
			gameEntity->render(renderer, textures);
			vector<GameEntity*> newGameEntities = gameEntity->getNewGameEntities();

			for (GameEntity* gameEntity : newGameEntities)
			{
				entityRepository->addEntity(gameEntity);
			}
			return true;
		}
	};
	entityRepository->iterate(renderEntities);

	SDL_RenderPresent(renderer);
	
	if (isGameOver)
	{
		unload();
	}

	return true;
}

bool Engine::Core::init()
{
	int windowPosX, windowPosY;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "Error initializing video" << endl;
		cout << SDL_GetError() << endl;
		return false;
	}
	Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_MOUSE_CAPTURE | SDL_WINDOW_SHOWN;
	if (SDL_GetNumVideoDisplays() > 1)
	{
		windowPosX = SDL_WINDOWPOS_CENTERED_DISPLAY(2);
		windowPosY = SDL_WINDOWPOS_CENTERED_DISPLAY(2);
	}
	else
	{
		windowPosX = SDL_WINDOWPOS_CENTERED;
		windowPosY = SDL_WINDOWPOS_CENTERED;
	}

	window = SDL_CreateWindow("Example", windowPosX, windowPosY, SCREEN_WIDTH, SCREEN_HEIGHT, flags);
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
	if (! renderer)
	{
		cout << "Could not initialize the renderer" << endl;
		cout << SDL_GetError() << endl;
		return false;
	}

	entityRepository = new GameEntityRepository();
	collisionDetector = new CollisionDetector(entityRepository);
	
	screenWriter = new ScreenWriter(renderer);
	if (! screenWriter->initialize())
	{
		return false;
	}

	isGameOver = true;

	return true;
}

bool Engine::Core::load()
{
	return screenWriter->load();
}

void Engine::Core::unload()
{
	entityRepository->clear();
}

void Engine::Core::kill()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
	delete entityRepository;
	delete screenWriter;
	SDL_Quit();
}
