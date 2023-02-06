#include <iostream>
#include <SDL2/SDL.h>
#include "constants.h"
#include "Bullet.h"
#include "Player.h"

#define MAX_ENTITIES 100

SDL_Window* window;
SDL_Renderer* renderer;

void init();
bool load();
void kill();
bool loop();

SDL_Point mousePosition;
SDL_Texture *textures[MAX_ENTITIES] = { nullptr };
GameEntity *gameEntities[MAX_ENTITIES] = { nullptr };
int gameEntitiesCount = 0;

int main()
{
	init();
	if (! load())
	{
		kill();
		return 0;
	}
	while (loop())
	{
		SDL_Delay(8);
	}

	kill();
	return 0;
}

bool loop()
{
	static const unsigned char* keys = SDL_GetKeyboardState( NULL );
	bool isMouseDown = false;
	SDL_GetGlobalMouseState(&mousePosition.x, &mousePosition.y);
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

	for (int i=0; i<MAX_ENTITIES; i++)
	{
		if (gameEntities[i])
		{
			gameEntities[i]->update(keys, mousePosition, isMouseDown);
			gameEntities[i]->render(renderer, textures);
			gameEntities[i]->addNewGameEntities(gameEntities, gameEntitiesCount);
		}
	}

	SDL_RenderPresent(renderer);

	return true;
}

void init()
{
	int windowPosX, windowPosY;
	SDL_Init(SDL_INIT_VIDEO);
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
}

bool load()
{
	Player *player = new Player(0, 0);
	bool resultPlayer = player->load(renderer, textures);

	Bullet *bullet = new Bullet(0, 0);
	bool resultBullet = bullet->load(renderer, textures);

	bullet = NULL;

	if (resultPlayer)
	{
		gameEntities[gameEntitiesCount++] = player;
	}

	return resultPlayer && resultBullet;
}

void kill()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	for (int i=0; i<MAX_ENTITIES; i++)
	{
		if (gameEntities[i])
		{
			gameEntities[i] = nullptr;
		}
	}

	renderer = NULL;
	window = NULL;
	SDL_Quit();
}
