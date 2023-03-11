#include <iostream>
#include <SDL2/SDL.h>
#include "constants.h"
#include "Entity.h"

void Engine::Entity::setId(unsigned int id)
{
	this->id = id;
}

unsigned int Engine::Entity::getId()
{
	return id;
}

int Engine::Entity::getX()
{
	return x;
}

int Engine::Entity::getY()
{
	return y;
}

int Engine::Entity::getHeight()
{
	return entityHeight;
}

int Engine::Entity::getWidth()
{
	return entityWidth;
}

bool Engine::Entity::load(SDL_Renderer* renderer, SDL_Texture* textures[])
{
	if (! textures[entityTextureIndex])
	{
		string BMPPath = ".\\" + ASSETS_FOLDER + "\\" + entityTextureFile;
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
			cout << SDL_GetError() << endl;
			return false;
		}

		SDL_FreeSurface(imageSurface);
	}

	return true;
}

void Engine::Entity::destroy(SDL_Texture* textures[])
{
	SDL_DestroyTexture(textures[entityTextureIndex]);
}
