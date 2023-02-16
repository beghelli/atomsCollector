#include <iostream>
#include <math.h>
#include <vector>
#include <SDL2/SDL.h>
#include "GameEntity.h"
#include "Atom.h"
#include <string>

GameEntities::Atom::Atom(int x, int y)
{
	this->x = x;
	this->y = y;
	this->originalX = x;
	this->originalY = y;
	this->xv = 0;
	this->yv = 0;
	this->zAngle = 0;
	this->acceleration = 2;
	this->isAcceleratingX = false;
	this->isAcceleratingY = false;
	this->entityHeight = 25;
	this->entityWidth = 25;
	this->entityTextureFile = "hidrogen.bmp";
	this->entityTextureIndex = 2;
}

void GameEntities::Atom::update(const unsigned char* keys, SDL_Point mousePosition, bool isMouseDown)
{
	x = originalX + (cos((zAngle + 180) / (180.0f / M_PI))*(xv));
	y = originalY + (sin((zAngle + 180) / (180.0f / M_PI))*(yv));
	xv += acceleration;
	yv += acceleration;
}

bool GameEntities::Atom::shouldDestroy()
{
	return reachedAnyScreenLimit();
}

bool GameEntities::Atom::processCollisions(vector<GameEntity*> collidingEntities)
{
	return collidingEntities.size() == 0;
}

void GameEntities::Atom::render(SDL_Renderer* renderer, SDL_Texture* textures[])
{
	SDL_Rect body;
	body.x = x;
	body.y = y;
	body.h = entityHeight;
	body.w = entityWidth;

	int result = SDL_RenderCopyEx(renderer, textures[entityTextureIndex], NULL, &body, zAngle, NULL, SDL_FLIP_NONE);

	if (result != 0)
	{
		cout << "Failed rendering hidrogen" << endl;
		cout << SDL_GetError() << endl;
	}
}

vector<GameEntity*> GameEntities::Atom::getNewGameEntities()
{
	vector<GameEntity*> entities;
	return entities;
}
