#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "GameEntity.h"

using namespace std;

class GameEntity
{

protected:
	unsigned int id;
	int x;
	int y;
	float xv;
	float yv;
	double zAngle;
	bool isAcceleratingX;
	bool isAcceleratingY;
	int currentMaxVelocity;
	int baseMaxVelocity;

	int entityHeight;
	int entityWidth;
	string entityTextureFile;
	int entityTextureIndex;
	struct
	{
		bool isOnLimitLeftX;
		bool isOnLimitRightX;
		bool isOnLimitTopY;
		bool isOnLimitBottomY;
	} limitPositionState;

	void updateScreenLimitPositionState();
	void limitPositionToScreenSize();
	bool reachedAnyScreenLimit();

public:
	void setId(unsigned int id);
	unsigned int getId();
	void setZAngle(double angle);
	bool load(SDL_Renderer* renderer, SDL_Texture* textures[]);
	void destroy(SDL_Texture* textures[]);

	virtual void update(const unsigned char* keys, SDL_Point mousePosition, bool isMouseDown)=0;
	virtual bool shouldDestroy()=0;
	virtual void render(SDL_Renderer* renderer, SDL_Texture* textures[])=0;
	virtual vector<GameEntity*> getNewGameEntities()=0;
};
