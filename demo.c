#include <iostream>
#include <SDL2/SDL.h>
#include "constants.h"
#include "Atom.h"
#include "Bullet.h"
#include "Player.h"
#include "GameEntityRepository.h"
#include "CollisionDetector.h"

#define MAX_ENTITIES 100

using namespace GameEntities;

SDL_Window* window;
SDL_Renderer* renderer;

bool init();
bool load();
void kill();
bool loop();
void fillAtoms();

SDL_Point mousePosition;
SDL_Texture *textures[MAX_ENTITIES] = { nullptr };
Support::GameEntityRepository* entityRepository;
Support::CollisionDetector* collisionDetector;

int main(int argc, char *argv[])
{
	if (init() && load())
	{
		while (loop())
		{
			SDL_Delay(18);
		}
	}

	kill();
	return 0;
}

bool loop()
{
	static const unsigned char* keys = SDL_GetKeyboardState( NULL );
	bool isMouseDown = false;
	SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
	SDL_Event e;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

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

	return true;
}

bool init()
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

	entityRepository = new Support::GameEntityRepository();
	fillAtoms();

	collisionDetector = new Support::CollisionDetector(entityRepository);
	
	return true;
}

void fillAtoms()
{
	struct AtomInfo {
		int x;
		int y;
		double zAngle;
	};

	AtomInfo atomsInfo[4];
	atomsInfo[0].x = 50;
	atomsInfo[0].y = 25;
	atomsInfo[0].zAngle = 180;

	atomsInfo[1].x = 500;
	atomsInfo[1].y = 400;
	atomsInfo[1].zAngle = 70;

	atomsInfo[2].x = 25;
	atomsInfo[2].y = 450;
	atomsInfo[2].zAngle = 140;

	atomsInfo[3].x = 300;
	atomsInfo[3].y = 50;
	atomsInfo[3].zAngle = -110;

	for (int i = 0; i < 4; i++)
	{
		Atom* atom = new Atom(atomsInfo[i].x, atomsInfo[i].y);
		atom->setZAngle(atomsInfo[i].zAngle);

		entityRepository->addEntity(atom);
	}
}

bool load()
{
	Player* player = new Player(0, 0);
	bool resultPlayer = player->load(renderer, textures);

	Bullet* bullet = new Bullet(0, 0);
	bool resultBullet = bullet->load(renderer, textures);
	delete bullet;
	
	Atom* atom = new Atom(0, 0);
	bool resultAtom = atom->load(renderer, textures);
	delete atom;

	if (resultPlayer)
	{
		entityRepository->addEntity(player);	
	}

	return resultPlayer && resultBullet && resultAtom;
}

void kill()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
	delete entityRepository;
	SDL_Quit();
}
