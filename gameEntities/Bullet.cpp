#include <math.h>
#include <vector>

#include "Bullet.h"
#include "Player.h"
#include "GameEntity.h"

using namespace std;
using namespace GameEntities;

GameEntities::Bullet::Bullet(int x, int y)
{
	this->x = x;
	this->y = y;
	this->originalX = x;
	this->originalY = y;
	this->xv = 1;
	this->yv = 1;
	this->zAngle = 0;
	this->acceleration = 10;
	this->isAcceleratingX = false;
	this->isAcceleratingY = false;
	this->entityHeight = 5;
	this->entityWidth = 5;
	this->entityTextureFile = "bullet.bmp";
	this->entityTextureIndex = 1;
	this->currentMaxVelocity = 16;
	this->baseMaxVelocity = this->currentMaxVelocity;
	this->initializeBodyCoordinates();
}

GameEntity* GameEntities::Bullet::getShooter()
{
	return shooterEntity;
}

void GameEntities::Bullet::setShooter(GameEntity* shooterEntity)
{
	this->shooterEntity = shooterEntity;
}

void GameEntities::Bullet::initializeBodyCoordinates()
{
	if (bodyCoordinatesX.size() == 0)
	{
		vector<int> firstRow{ 0,  2,  3,  4,  0 };
		this->bodyCoordinatesX.push_back(firstRow);

		vector<int> secondRow{ 1,  2,  3,  4,  5 };
		this->bodyCoordinatesX.push_back(secondRow);
		
		this->bodyCoordinatesX.push_back(bodyCoordinatesX[1]);
		this->bodyCoordinatesX.push_back(bodyCoordinatesX[1]);
		this->bodyCoordinatesX.push_back(bodyCoordinatesX[0]);
	}

	if (bodyCoordinatesY.size() == 0)
	{
		this->bodyCoordinatesY.push_back({ 0,  1,  1,  1,  0 });
		this->bodyCoordinatesY.push_back({ 2,  2,  2,  2,  2 });
		this->bodyCoordinatesY.push_back(bodyCoordinatesY[1]);
		this->bodyCoordinatesY.push_back(bodyCoordinatesY[1]);
		this->bodyCoordinatesY.push_back(bodyCoordinatesY[0]);
	}
}

void GameEntities::Bullet::render(SDL_Renderer* renderer, SDL_Texture* textures[])
{
	SDL_Rect body;
	body.x = x;
	body.y = y;
	body.h = entityHeight;
	body.w = entityWidth;

	int result = SDL_RenderCopyEx(renderer, textures[entityTextureIndex], NULL, &body, zAngle, NULL, SDL_FLIP_NONE);

	if (result != 0)
	{
		cout << "Failed rendering bullet" << endl;
		cout << SDL_GetError() << endl;
	}
}

void GameEntities::Bullet::update(const unsigned char* keys, SDL_Point mousePosition, bool isMouseDown)
{
	x = originalX + (cos((zAngle + 180) / (180.0f / M_PI))*(xv));
	y = originalY + (sin((zAngle + 180) / (180.0f / M_PI))*(yv));
	xv += acceleration;
	yv += acceleration;
}

bool GameEntities::Bullet::shouldDestroy()
{
	return reachedAnyScreenLimit();
}

bool GameEntities::Bullet::processCollisions(vector<GameEntity*> collidingEntities)
{
	bool shouldKeepThis = true;
	for (GameEntity* gameEntity : collidingEntities)
	{
		if (gameEntity->getId() != shooterEntity->getId())
		{
			shouldKeepThis = false;
		}
	}

	return shouldKeepThis; 
}

vector<GameEntity*> GameEntities::Bullet::getNewGameEntities()
{
	vector<GameEntity*> entities;
	return entities;
}
