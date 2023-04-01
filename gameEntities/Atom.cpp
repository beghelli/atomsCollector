#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include "constants.h"
#include "GameEntity.h"
#include "ScreenWriter.h"
#include "Atom.h"
#include "AtomDAO.h"
#include "MetricManager.h"

using namespace Engine::Support;
using namespace Data;

GameEntities::Atom::Atom(int x, int y, int atomicNumber, int atomicMass)
{
	this->x = x;
	this->y = y;
	this->originalX = x;
	this->originalY = y;
	this->xv = 0;
	this->yv = 0;
	this->zAngle = 0;
	this->acceleration = Engine::MetricManager::unitToPixels(0.02);
	this->isAcceleratingX = false;
	this->isAcceleratingY = false;
	this->entityHeight = (int) Engine::MetricManager::unitToPixelsY(0.25);
	this->entityWidth = (int) Engine::MetricManager::unitToPixelsX(0.25);
	this->entityTextureFile = "hidrogen.bmp";
	this->entityTextureIndex = 2;
	this->type = "Atom";
	this->atomicNumber = atomicNumber;
	this->atomicMass = atomicMass;
}

bool GameEntities::Atom::load(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter)
{
	bool loadedDataRepository = AtomDAO::loadData();

	return Engine::Entity::load(renderer, textures, screenWriter) && loadedDataRepository;
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

bool GameEntities::Atom::isGameOver()
{
	return false;
}

bool GameEntities::Atom::processCollisions(vector<GameEntity*> collidingEntities)
{
	return collidingEntities.size() == 0;
}

void GameEntities::Atom::render(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter)
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
