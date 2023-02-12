#include <math.h>
#include <vector>
#include "Bullet.h"
#include "GameEntity.h"

using namespace std;

Bullet::Bullet(int x, int y)
{
	this->x = x;
	this->y = y;
	this->originalX = x;
	this->originalY = y;
	this->xv = 1;
	this->yv = 1;
	this->zAngle = 0;
	this->isAcceleratingX = false;
	this->isAcceleratingY = false;
	this->entityHeight = 5;
	this->entityWidth = 5;
	this->entityTextureFile = "bullet.bmp";
	this->entityTextureIndex = 1;
}

void Bullet::render(SDL_Renderer* renderer, SDL_Texture* textures[])
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

void Bullet::update(const unsigned char* keys, SDL_Point mousePosition, bool isMouseDown)
{
	x = originalX + (cos((zAngle + 180) / (180.0f / M_PI))*(xv++));
	y = originalY + (sin((zAngle + 180) / (180.0f / M_PI))*(yv++));
}

bool Bullet::shouldDestroy()
{
	return reachedAnyScreenLimit();
}

vector<GameEntity*> Bullet::getNewGameEntities()
{
	vector<GameEntity*> entities;
	return entities;
}
