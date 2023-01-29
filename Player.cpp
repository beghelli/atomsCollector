#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "constants.h"
#include "Player.h"

using namespace std;

const int PLAYER_HEIGHT = 25;
const int PLAYER_WIDTH = 25;
const string PLAYER_TEXTURE_FILE = "player.bmp";

SDL_Texture* texture;

Player::Player(int x, int y)
{
	this->x = x;
	this->y = y;
	this->xv = 0;
	this->yv = 0;
	this->isAcceleratingX = false;
	this->isAcceleratingY = false;
}

bool Player::load(SDL_Renderer* renderer)
{
	string BMPPath = "./" + ASSETS_FOLDER + "/" + PLAYER_TEXTURE_FILE;
	SDL_Surface* imageSurface = SDL_LoadBMP(BMPPath.c_str());
	if (! imageSurface)
	{
		cout << "Failed loading player texture image" << endl;
		cout << "Player texture image path: " << BMPPath << endl;
		return false;
	}
	texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
	if (! texture)
	{
		cout << "Failed loading player texture." << endl;
		return false;
	}

	cout << "1st Texture dump:" << texture << endl;

	SDL_FreeSurface(imageSurface);
	imageSurface = NULL;

	return true;
}

void Player::applyInputs(const unsigned char* keys, SDL_Point mousePosition)
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

	if (y + PLAYER_HEIGHT >= SCREEN_HEIGHT)
	{
		yv = 0;
		y = SCREEN_HEIGHT - PLAYER_HEIGHT;
	}

	if (y < 0)
	{
		yv = 0;
		y = 0;
	}

	if (x + PLAYER_WIDTH >= SCREEN_WIDTH)
	{
		xv = 0;
		x = SCREEN_WIDTH - PLAYER_WIDTH;
	}

	if (x < 0)
	{
		xv = 0;
		x = 0;
	}

	if (DEBUG)
	{
		cout << "Player Y velocity: " << yv << endl;
		cout << "Accelerating Y: " << isAcceleratingY << endl;
		cout << "Player X velocity: " << xv << endl;
		cout << "Accelerating X: " << isAcceleratingX << endl;
		cout << "Mouse X: " << mousePosition.x << endl;
		cout << "Mouse Y: " << mousePosition.y << endl;
	}
}

void Player::render(SDL_Renderer* renderer)
{
	SDL_Rect body;
	body.x = x;
	body.y = y;
	body.h = PLAYER_HEIGHT;
	body.w = PLAYER_WIDTH;
	int result = SDL_RenderCopy(renderer, texture, NULL, &body);

	if (result != 0)
	{
		cout << "Failed rendering player" << endl;
		cout << SDL_GetError() << endl;
	}
}

void Player::destroy()
{
	SDL_DestroyTexture(texture);
	texture = NULL;
}
