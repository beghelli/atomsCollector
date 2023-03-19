#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "constants.h"
#include "Bullet.h"
#include "GameEntity.h"
#include "Player.h"
#include "Atom.h"
#include "ScreenWriter.h"
#include "PlayerAndAtomCollided.h"
#include "MetricManager.h"

using namespace std;
using namespace Engine;
using namespace Support;
using namespace Events;

bool isFiring = false;

GameEntities::Player::Player(int x, int y)
{
	this->x = x;
	this->y = y;
	this->xv = 0;
	this->yv = 0;
	this->zAngle = 0;
	this->acceleration = 0.5;
	this->isAcceleratingX = false;
	this->isAcceleratingY = false;
	this->entityHeight = Engine::MetricManager::unitToPixelsY(0.5);
	this->entityWidth = Engine::MetricManager::unitToPixelsX(0.55);
	this->entityTextureFile = "player.bmp";
	this->entityTextureIndex = 0;
	this->currentMaxVelocity = 4;
	this->baseMaxVelocity = this->currentMaxVelocity;
	this->isRunning = false;
	this->type = "Player";
}

void GameEntities::Player::setLife(int life)
{
	this->life = life;
}

int GameEntities::Player::getLife()
{
	return life;
}

void GameEntities::Player::update(const unsigned char* keys, SDL_Point mousePosition, bool isMouseDown)
{
	isRunning = keys[SDL_SCANCODE_LSHIFT];

	calculatePosition(keys);
	limitPositionToScreenSize();
	calculateZAngle(mousePosition);
	isFiring = isMouseDown;

	if (DEBUG)
	{
		if (keys[DEBUG_KEY])
		{
			cout << "Player X,Y position: " << x << ',' << y << endl;
			cout << "Player Y velocity: " << yv << endl;
			cout << "Accelerating Y: " << isAcceleratingY << endl;
			cout << "Player X velocity: " << xv << endl;
			cout << "Accelerating X: " << isAcceleratingX << endl;
			cout << "Mouse X,Y: " << mousePosition.x << ',' << mousePosition.y << endl;
			cout << "Angle: " << zAngle << endl;
			cout << "Is mouse down: " << isMouseDown << endl;
			cout << "====================" << endl;
		}
	}
}

bool GameEntities::Player::shouldDestroy()
{
	return false;
}

bool GameEntities::Player::isGameOver()
{
	return this->life <= 0;
}

bool GameEntities::Player::processCollisions(vector<GameEntity*> collidingEntities)
{
	for (GameEntity* gameEntity : collidingEntities)
	{
		if (gameEntity->type == "Atom")
		{
			Atom* atom = dynamic_cast<Atom*>(gameEntity);
			PlayerAndAtomCollided* event = new PlayerAndAtomCollided(atom->atomicNumber, atom->atomicMass);
			event->trigger();
		}
	}

	return true;
}

void GameEntities::Player::render(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter)
{
	SDL_Rect body;
	body.x = x;
	body.y = y;
	body.h = entityHeight;
	body.w = entityWidth;

	int result = SDL_RenderCopyEx(renderer, textures[entityTextureIndex], NULL, &body, zAngle, NULL, SDL_FLIP_NONE);

	if (result != 0)
	{
		cout << "Failed rendering player" << endl;
		cout << SDL_GetError() << endl;
	}
}

vector<GameEntity*> GameEntities::Player::getNewGameEntities()
{
	vector<GameEntity*> entities;
	if (isFiring)
	{
		Bullet* bullet = new Bullet(x + entityWidth / 2, y + entityHeight / 2);
		bullet->setZAngle(zAngle);
		float currentMovingSpeed = getCurrentMovingSpeed();
		bullet->increaseAccelerationIn(currentMovingSpeed);
		bullet->setShooter(this);
		entities.push_back(bullet);
	}
	return entities;
}

void GameEntities::Player::calculateZAngle(SDL_Point mousePosition)
{
	int mX = (x + entityWidth / 2) - mousePosition.x;
	int mY = (y + entityHeight / 2) - mousePosition.y;
	zAngle = atan2((float) mY, (float) mX) * (180.0f / M_PI);
}

void GameEntities::Player::calculatePosition(const unsigned char* keys)
{
	currentMaxVelocity = baseMaxVelocity;
	if (isRunning)
	{
		currentMaxVelocity *= 3;
	}

	// Y Axis;
	if (keys[SDL_SCANCODE_S])
	{
		if (yv < currentMaxVelocity)
		{
			yv += acceleration;
			isAcceleratingY = true;
		}
		else if (yv > currentMaxVelocity)
		{
			isAcceleratingY = false;
		}
		else
		{
			isAcceleratingY = true;
		}
	}
	else if (keys[SDL_SCANCODE_W])
	{
		if (yv > -currentMaxVelocity)
		{
			yv -= acceleration;
			isAcceleratingY = true;
		}
		else if (yv < -currentMaxVelocity)
		{
			isAcceleratingY = false;
		}
		else
		{
			isAcceleratingY = true;
		}
	}
	else
	{
		isAcceleratingY = false;
	}

	// X Axis;
	if (keys[SDL_SCANCODE_A])
	{
		if (xv > -currentMaxVelocity)
		{
			xv -= acceleration;
			isAcceleratingX = true;
		}
		else if (xv < -currentMaxVelocity)
		{
			isAcceleratingX = false;
		}
		else
		{
			isAcceleratingX = true;
		}
	}
	else if (keys[SDL_SCANCODE_D])
	{
		if (xv < currentMaxVelocity)
		{
			xv += acceleration;
			isAcceleratingX = true;
		}
		else if (xv > currentMaxVelocity)
		{
			isAcceleratingX = false;
		}
		else
		{
			isAcceleratingX = true;
		}
	}
	else
	{
		isAcceleratingX = false;
	}

	if (yv != 0 && ! isAcceleratingY)
	{
		if (yv > 0)
		{
			yv -= acceleration;
			if (yv < 0)
			{
				yv = 0;
			}
		}
		else
		{
			yv += acceleration;
			if (yv > 0)
			{
				yv = 0;
			}
		}
	}

	if (xv != 0 && ! isAcceleratingX)
	{
		if (xv > 0)
		{
			xv -= acceleration;
			if (xv < 0)
			{
				xv = 0;
			}
		}
		else
		{
			xv += acceleration;
			if (xv > 0)
			{
				xv = 0;
			}
		}
	}

	float finalXV = xv;
	float finalYV = yv;

	if (yv && xv)
	{
		finalXV = (xv / 100) * 85;
		finalYV = (yv / 100) * 85;
		if (finalXV > 0)
		{
			finalXV = floor(finalXV);
		}
		else
		{
			finalXV = ceil(finalXV);
		}
		if (finalYV > 0)
		{
			finalYV = floor(finalYV);
		}
		else
		{
			finalYV = ceil(finalYV);
		}
	}

	y += finalYV;
	x += finalXV;
}

float GameEntities::Player::getCurrentMovingSpeed()
{
	float currentMovingSpeed = 0;
	if (xv != 0)
	{
		if (xv > 0)
		{
			if (zAngle > 135.000 || zAngle < -135.000)
			{
				currentMovingSpeed = xv;
			}
		}
		else
		{
			if (zAngle < 45.000 && zAngle > -45.000)
			{
				currentMovingSpeed = abs(xv);
			}
		}
	}

	if (yv != 0)
	{
		if (yv > 0)
		{
			if (zAngle < -45.000 && zAngle > -135.000)
			{
				currentMovingSpeed = yv;
			}
		}
		else
		{
			if (zAngle > 45.000 && zAngle < 135.000)
			{
				currentMovingSpeed = abs(yv);
			}
		}
	}

	return currentMovingSpeed;
}

