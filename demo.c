#include <iostream>
#include <SDL2/SDL.h>
#include "constants.h"
#include "Player.h"

SDL_Window* window;
SDL_Renderer* renderer;

void init();
bool load();
void kill();
bool loop();

Player* player;
SDL_Point mousePosition;

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
		SDL_Delay(10);
	}

	kill();
	return 0;
}

bool loop()
{
	static const unsigned char* keys = SDL_GetKeyboardState( NULL );
	bool isMouseDown;
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

	player->applyInputs(keys, mousePosition, isMouseDown);
	player->render(renderer);

	SDL_RenderPresent(renderer);

	return true;
}

void init()
{
	window = SDL_CreateWindow( "Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
}

bool load()
{
	player = new Player(0, 0);
	bool result = player->load(renderer);

	return result;
}

void kill()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	player->destroy();
	renderer = NULL;
	window = NULL;
	player = NULL;
	SDL_Quit();
}
