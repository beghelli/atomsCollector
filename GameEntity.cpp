#include <iostream>
#include <SDL2/SDL.h>
#include "GameEntity.h"
#include "constants.h"

void GameEntity::setZAngle(double angle)
{
	this->zAngle = angle;
}

void GameEntity::updateScreenLimitPositionState()
{
	this->limitPositionState.isOnLimitBottomY = (y + entityHeight) > SCREEN_HEIGHT;
	this->limitPositionState.isOnLimitTopY = y < 0;

	this->limitPositionState.isOnLimitRightX = (x + entityWidth) > SCREEN_WIDTH;
	this->limitPositionState.isOnLimitLeftX = x < 0;
}

void GameEntity::limitPositionToScreenSize()
{
	updateScreenLimitPositionState();
	if (limitPositionState.isOnLimitBottomY)
	{
		yv = 0;
		y = SCREEN_HEIGHT - entityHeight;
	}

	if (limitPositionState.isOnLimitTopY)
	{
		yv = 0;
		y = 0;
	}

	if (limitPositionState.isOnLimitRightX)
	{
		xv = 0;
		x = SCREEN_WIDTH - entityWidth;
	}

	if (limitPositionState.isOnLimitLeftX)
	{
		xv = 0;
		x = 0;
	}
}

bool GameEntity::reachedAnyScreenLimit()
{
	updateScreenLimitPositionState();

	return limitPositionState.isOnLimitLeftX || limitPositionState.isOnLimitRightX 
		|| limitPositionState.isOnLimitBottomY || limitPositionState.isOnLimitTopY;
}

bool GameEntity::load(SDL_Renderer* renderer, SDL_Texture* textures[])
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
		SDL_Texture *texturemageSurface = NULL;
	}

	return true;
}

void GameEntity::destroy(SDL_Texture* textures[])
{
	SDL_DestroyTexture(textures[entityTextureIndex]);
}
