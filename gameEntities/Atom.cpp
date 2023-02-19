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
	this->initializeBodyCoordinates();
}

void GameEntities::Atom::initializeBodyCoordinates()
{
	this->bodyCoordinatesX.push_back({ 0, 0, 0, 0, 0, 0, 0, 0, 9, 10, 11, 12, 13, 14, 15, 16, 17,  0,  0,  0,  0,  0,  0,   0,  0 });
	this->bodyCoordinatesX.push_back({ 0, 0, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,  0,  0,  0,  0,   0,  0 });
	this->bodyCoordinatesX.push_back({ 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,  0,  0,   0,  0 });
	this->bodyCoordinatesX.push_back({ 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,  0,   0,  0 });
	this->bodyCoordinatesX.push_back({ 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,   0,  0 });
	this->bodyCoordinatesX.push_back({ 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,   0,  0 });
	this->bodyCoordinatesX.push_back({ 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,  24,  0 });
	this->bodyCoordinatesX.push_back({ 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,  24,  0 });
	this->bodyCoordinatesX.push_back({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,  24, 25 });
	this->bodyCoordinatesX.push_back({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,  24, 25 });
	this->bodyCoordinatesX.push_back({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,  24, 25 });
	this->bodyCoordinatesX.push_back({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,  24, 25 });
	this->bodyCoordinatesX.push_back({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,  24, 25 });
	this->bodyCoordinatesX.push_back({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,  24, 25 });
	this->bodyCoordinatesX.push_back({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,  24, 25 });
	this->bodyCoordinatesX.push_back({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,  24, 25 });
	this->bodyCoordinatesX.push_back({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,  24, 25 });
	this->bodyCoordinatesX.push_back({ 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,  24,  0 });
	this->bodyCoordinatesX.push_back({ 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,  24,  0 });
	this->bodyCoordinatesX.push_back({ 0, 0, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,   0,  0 });
	this->bodyCoordinatesX.push_back({ 0, 0, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,   0,  0 });
	this->bodyCoordinatesX.push_back({ 0, 0, 0, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,  0,   0,  0 });
	this->bodyCoordinatesX.push_back({ 0, 0, 0, 0, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,  0,  0,   0,  0 });
	this->bodyCoordinatesX.push_back({ 0, 0, 0, 0, 0, 0, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,  0,  0,  0,  0,   0,  0 });
	this->bodyCoordinatesX.push_back({ 0, 0, 0, 0, 0, 0, 0, 0, 9, 10, 11, 12, 13, 14, 15, 16, 17,  0,  0,  0,  0,  0,  0,   0,  0 });

	this->bodyCoordinatesY.push_back({ 0, 0, 0, 0, 0, 0, 0, 0, 1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,   0,  0 });
	this->bodyCoordinatesY.push_back({ 0, 0, 2, 2, 2, 2, 2, 2, 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  0,  0,  0,  0,   0,  0 });
	this->bodyCoordinatesY.push_back({ 0, 3, 3, 3, 3, 3, 3, 3, 3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  0,  0,   0,  0 });
	this->bodyCoordinatesY.push_back({ 0, 4, 4, 4, 4, 4, 4, 4, 4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  0,   0,  0 });
	this->bodyCoordinatesY.push_back({ 0, 5, 5, 5, 5, 5, 5, 5, 5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,   0,  0 });
	this->bodyCoordinatesY.push_back({ 0, 6, 6, 6, 6, 6, 6, 6, 6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,   0,  0 });
	this->bodyCoordinatesY.push_back({ 0, 7, 7, 7, 7, 7, 7, 7, 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,   7,  0 });
	this->bodyCoordinatesY.push_back({ 0, 8, 8, 8, 8, 8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,   8,  0 });
	this->bodyCoordinatesY.push_back({ 9, 9, 9, 9, 9, 9, 9, 9, 9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,   9,  9 });
	this->bodyCoordinatesY.push_back(vector<int>(25,10));
	this->bodyCoordinatesY.push_back(vector<int>(25,11));
	this->bodyCoordinatesY.push_back(vector<int>(25,12));
	this->bodyCoordinatesY.push_back(vector<int>(25,13));
	this->bodyCoordinatesY.push_back(vector<int>(25,14));
	this->bodyCoordinatesY.push_back(vector<int>(25,15));
	this->bodyCoordinatesY.push_back(vector<int>(25,16));
	this->bodyCoordinatesY.push_back(vector<int>(25,17));
	int i = 18;
	this->bodyCoordinatesY.push_back({ 0, i, i, i, i, i, i, i, i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,   i,  0 });
	i = 19;
	this->bodyCoordinatesY.push_back({ 0, i, i, i, i, i, i, i, i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,   i,  0 });
	i = 20;
	this->bodyCoordinatesY.push_back({ 0, 0, i, i, i, i, i, i, i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,   0,  0 });
	i = 21;
	this->bodyCoordinatesY.push_back({ 0, 0, i, i, i, i, i, i, i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,   0,  0 });
	i = 22;
	this->bodyCoordinatesY.push_back({ 0, 0, 0, i, i, i, i, i, i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  0,   0,  0 });
	i = 23;
	this->bodyCoordinatesY.push_back({ 0, 0, 0, 0, i, i, i, i, i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  0,  0,   0,  0 });
	i = 24;
	this->bodyCoordinatesY.push_back({ 0, 0, 0, 0, 0, 0, i, i, i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  0,  0,  0,  0,   0,  0 });
	i = 25;
	this->bodyCoordinatesY.push_back({ 0, 0, 0, 0, 0, 0, 0, 0, i,  i,  i,  i,  i,  i,  i,  i,  i,  0,  0,  0,  0,  0,  0,   0,  0 });
}

void GameEntities::Atom::update(const unsigned char* keys, SDL_Point mousePosition, bool isMouseDown)
{
	if (reachedAnyScreenLimit())
	{
		if (limitPositionState.isOnLimitBottomY
			|| limitPositionState.isOnLimitTopY)
		{
			zAngle *= -1;
		}
		
		if (limitPositionState.isOnLimitRightX
			|| limitPositionState.isOnLimitLeftX)
		{
			zAngle = 180 - zAngle;
		}
		originalX = x;
		originalY = y;
		xv = acceleration;
		yv = acceleration;
	}

	x = originalX + (cos((zAngle + 180) / (180.0f / M_PI))*(xv));
	y = originalY + (sin((zAngle + 180) / (180.0f / M_PI))*(yv));
	xv += acceleration;
	yv += acceleration;
}

bool GameEntities::Atom::shouldDestroy()
{
	return false;
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
