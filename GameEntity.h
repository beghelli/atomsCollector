#pragma once
#include <SDL2/SDL.h>
#include <string>

using namespace std;

class GameEntity
{

protected:
	int x;
	int y;
	float xv;
	float yv;
	double zAngle;
	bool isAcceleratingX;
	bool isAcceleratingY;

	int entityHeight;
	int entityWidth;
	string entityTextureFile;
	int entityTextureIndex;

	void limitPositionToScreenSize();

public:
	bool load(SDL_Renderer* renderer, SDL_Texture* textures[]);
	void destroy(SDL_Texture* textures[]);

	virtual void update(const unsigned char* keys, SDL_Point mousePosition, bool isMouseDown)=0;
	virtual void render(SDL_Renderer* renderer, SDL_Texture* textures[])=0;
};
