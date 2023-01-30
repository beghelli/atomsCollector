#include "Bullet.h"

Bullet::Bullet(int x, int y)
{
	this->x = x;
	this->y = y;
	this->xv = 0;
	this->yv = 0;
	this->zAngle = 0;
	this->isAcceleratingX = false;
	this->isAcceleratingY = false;
	this->entityHeight = 5;
	this->entityWidth = 5;
	this->entityTextureFile = "bullet.png";
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
}
