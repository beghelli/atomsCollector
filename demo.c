#include <iostream>
#include <SDL2/SDL.h>
#include "constants.h"
#include "Bullet.h"
#include "Player.h"
#include "GameEntityRepository.h"

#define MAX_ENTITIES 100

SDL_Window* window;
SDL_Renderer* renderer;

bool init();
bool load();
void kill();
bool loop();

SDL_Point mousePosition;
SDL_Texture *textures[MAX_ENTITIES] = { nullptr };
Support::GameEntityRepository* entityRepository;

int main(int argc, char *argv[])
{
	if (init() && load())
	{
		while (loop())
		{
			SDL_Delay(8);
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

	auto processEntities = [&](unsigned int id, GameEntity* gameEntity) -> bool
	{
		gameEntity->update(keys, mousePosition, isMouseDown); 
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

	entityRepository->iterate(processEntities);

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
	
	return true;
}

bool load()
{
	Player *player = new Player(0, 0);
	bool resultPlayer = player->load(renderer, textures);

	Bullet *bullet = new Bullet(0, 0);
	bool resultBullet = bullet->load(renderer, textures);

	delete bullet;

	if (resultPlayer)
	{
		entityRepository->addEntity(player);	
	}

	return resultPlayer && resultBullet;
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
