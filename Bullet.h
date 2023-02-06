#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include "GameEntity.h"

class Bullet : public GameEntity{

public:
	Bullet(int x, int y);

	void update(const unsigned char* keys, SDL_Point mousePosition, bool isMouseDown);
	void render(SDL_Renderer* renderer, SDL_Texture* textures[]);
	void addNewGameEntities(GameEntity* gameEntities[], int gameEntitiesCount);

private:
	int originalX;
	int originalY;

};
