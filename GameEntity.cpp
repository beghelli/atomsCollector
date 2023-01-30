#include <iostream>
#include <SDL2/SDL.h>
#include "GameEntity.h"
#include "constants.h"

void GameEntity::limitPositionToScreenSize()
{
	if (y + entityHeight >= SCREEN_HEIGHT)
	{
		yv = 0;
		y = SCREEN_HEIGHT - entityHeight;
	}

	if (y < 0)
	{
		yv = 0;
		y = 0;
	}

	if (x + entityWidth >= SCREEN_WIDTH)
	{
		xv = 0;
		x = SCREEN_WIDTH - entityWidth;
	}

	if (x < 0)
	{
		xv = 0;
		x = 0;
	}
};

bool GameEntity::load(SDL_Renderer* renderer, SDL_Texture* textures[])
{
	if (! textures[entityTextureIndex])
	{
		string BMPPath = "./" + ASSETS_FOLDER + "/" + entityTextureFile;
		SDL_Surface* imageSurface = SDL_LoadBMP(BMPPath.c_str());
		if (! imageSurface)
		{
			cout << "Failed loading texture image" << endl;
			cout << "Texture image path: " << BMPPath << endl;
			return false;
		}
		textures[entityTextureIndex] = SDL_CreateTextureFromSurface(renderer, imageSurface);
		if (! textures[entityTextureIndex])
		{
			cout << "Failed loading texture." << endl;
			return false;
		}

		SDL_FreeSurface(imageSurface);
		SDL_Texture *texturemageSurface = NULL;
	}

	return true;
}

void GameEntity::destroy(SDL_Texture* textures[])
{
	SDL_DestroyTexture(textures[entityTextureIndex]);
}
