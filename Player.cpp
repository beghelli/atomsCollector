#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "constants.h"
#include "Bullet.h"
#include "GameEntity.h"
#include "Player.h"

using namespace std;

bool isFiring = false;

Player::Player(int x, int y)
{
	this->x = x;
	this->y = y;
	this->xv = 0;
	this->yv = 0;
	this->zAngle = 0;
	this->isAcceleratingX = false;
	this->isAcceleratingY = false;
	this->entityHeight = 25;
	this->entityWidth = 25;
	this->entityTextureFile = "player.bmp";
	this->entityTextureIndex = 0;
}

void Player::update(const unsigned char* keys, SDL_Point mousePosition, bool isMouseDown)
{
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

bool Player::shouldDestroy()
{
	return false;
}

void Player::render(SDL_Renderer* renderer, SDL_Texture* textures[])
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

vector<GameEntity*> Player::getNewGameEntities()
{
	vector<GameEntity*> entities;
	if (isFiring)
	{
		Bullet* bullet = new Bullet(x + entityWidth / 2, y + entityHeight / 2);
		bullet->setZAngle(zAngle);
		entities.push_back(bullet);
	}
	return entities;
}

void Player::calculateZAngle(SDL_Point mousePosition)
{
	int mX = (x + entityWidth / 2) - mousePosition.x;
	int mY = (y + entityHeight / 2) - mousePosition.y;
	zAngle = atan2((float) mY, (float) mX) * (180.0f / M_PI);
}

void Player::calculatePosition(const unsigned char* keys)
{
	// Y Axis;
	if (keys[SDL_SCANCODE_S])
	{
		yv += ACCELERATION;
		isAcceleratingY = true;
	}
	else if (keys[SDL_SCANCODE_W])
	{
		yv -= ACCELERATION;
		isAcceleratingY = true;
	}
	else
	{
		isAcceleratingY = false;
	}

	// X Axis;
	if (keys[SDL_SCANCODE_A])
	{
		xv -= ACCELERATION;
		isAcceleratingX = true;
	}
	else if (keys[SDL_SCANCODE_D])
	{
		xv += ACCELERATION;
		isAcceleratingX = true;
	}
	else
	{
		isAcceleratingX = false;
	}

	if (yv != 0 && ! isAcceleratingY)
		if (yv > 0)
			yv -= ACCELERATION;
		else
			yv += ACCELERATION;

	if (xv != 0 && ! isAcceleratingX)
		if (xv > 0)
			xv -= ACCELERATION;
		else
			xv += ACCELERATION;

	y += yv;
	x += xv;
}
