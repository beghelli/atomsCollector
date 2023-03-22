#include <iostream>
#include <thread>
#include <functional>
#include <SDL2/SDL.h>
#include "Core.h"
#include "Game.h"
#include "constants.h"
#include "EntityRepository.h"
#include "CollisionDetector.h"
#include "ScreenWriter.h"

using namespace std;
using namespace Support;

Engine::Core::Core(Game* game)
{
	this->game = game;
}

int Engine::Core::run()
{
	if (init() && load() && game->load(renderer, textures, screenWriter))
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

	switch (game->status)
	{
		case Game::STATUS_OUT_GAME:
			return game->renderMenus(renderer, textures, screenWriter, keys, isMouseDown);
			break;
		case Game::STATUS_IN_GAME:
			return gameLoop(keys, isMouseDown);
			break;
		case Game::STATUS_LOADING:
			if (game->loadingQueue.size() > 0)
			{
				thread loadingTask(runGameLoaders, this);
				loadingTask.detach();
			}
			game->renderLoadingScreen(renderer, textures, screenWriter, keys, isMouseDown);
			return true;
			break;
	}

	return false;
}

void Engine::Core::runGameLoaders(Core* core)
{
	auto workingQueue = core->game->loadingQueue;
	core->game->loadingQueue.clear();
	for (function<void(EntityRepository<GameEntity>* entityRepository, EntityRepository<Entity>* UIEntityRepository)> loader : workingQueue)
	{
		loader(core->entityRepository, core->UIEntityRepository);
	}
}

bool Engine::Core::gameLoop(const unsigned char* keys, bool isMouseDown)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	game->currentGameScene->onGameLoopStart(entityRepository, UIEntityRepository, screenWriter, keys, isMouseDown);

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
		if (game->status != Game::STATUS_IN_GAME)
		{
			return false;
		}

		if (gameEntity->isGameOver())
		{
			game->status = Game::STATUS_OUT_GAME;
		}
		if (gameEntity->shouldDestroy())
		{
			return false;
		}
		else
		{
			gameEntity->render(renderer, textures, screenWriter);
			vector<GameEntity*> newGameEntities = gameEntity->getNewGameEntities();

			for (GameEntity* gameEntity : newGameEntities)
			{
				entityRepository->addEntity(gameEntity);
			}
			return true;
		}
	};
	entityRepository->iterate(renderEntities);

	auto renderUIEntities = [&](unsigned int id, Entity* UIEntity) -> bool
	{
		UIEntity->render(renderer, textures, screenWriter);
		return true;
	};

	UIEntityRepository->iterate(renderUIEntities);

	SDL_RenderPresent(renderer);

	if (game->status != Game::STATUS_IN_GAME)
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
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "2");
	Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_MOUSE_CAPTURE;
	if (FULLSCREEN)
	{
		flags = flags | SDL_WINDOW_FULLSCREEN;
	}
	else
	{
		flags = flags | SDL_WINDOW_SHOWN;
	}

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

	entityRepository = new EntityRepository<GameEntity>();
	UIEntityRepository = new EntityRepository<Entity>();
	collisionDetector = new CollisionDetector(entityRepository);

	screenWriter = new ScreenWriter(renderer);
	if (! screenWriter->initialize())
	{
		return false;
	}

	game->status = Game::STATUS_OUT_GAME;

	return true;
}

bool Engine::Core::load()
{
	return screenWriter->load();
}

void Engine::Core::unload()
{
	entityRepository->clear();
	UIEntityRepository->clear();
}

void Engine::Core::kill()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
	delete entityRepository;
	delete UIEntityRepository;
	delete screenWriter;
	SDL_Quit();
}
