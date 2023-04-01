#include <iostream>
#include <SDL2/SDL.h>
#include "constants.h"
#include "Entity.h"
#include "ScreenWriter.h"

using namespace Engine::Support;

const string Engine::Entity::DEFAULT_INSTANCE_TYPE = "0";

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

string Engine::Entity::getClassType()
{
	return classType;
}

string Engine::Entity::getInstanceType()
{
	if (instanceType.length() == 0)
	{
		return instanceType;
	}
	else
	{
		return DEFAULT_INSTANCE_TYPE;
	}
}

bool Engine::Entity::load(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter)
{
	if (! entityTextureFile.empty() && ! textures[entityTextureIndex])
	{
		string BMPPath = "." + PATH_SEPARATOR + ASSETS_FOLDER + PATH_SEPARATOR + entityTextureFile;
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
	if (! entityTextureFile.empty())
	{
		SDL_DestroyTexture(textures[entityTextureIndex]);
	}
}
