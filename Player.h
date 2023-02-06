#pragma once
#include <SDL2/SDL.h>
#include "GameEntity.h"

class Player : public GameEntity
{

private:
	void calculatePosition(const unsigned char* keys);
	void calculateZAngle(SDL_Point mousePosition);
	void fire(bool isMouseDown);

public:
	Player(int x, int y);

	void update(const unsigned char* keys, SDL_Point mousePosition, bool isMouseDown);
	void render(SDL_Renderer* renderer, SDL_Texture* textures[]);
	void addNewGameEntities(GameEntity* gameEntities[], int gameEntitiesCount);
};
