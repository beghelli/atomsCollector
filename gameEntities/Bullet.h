#pragma once
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "GameEntity.h"

using namespace std;
using namespace GameEntities;

namespace GameEntities 
{
	class Bullet : public GameEntity{

	public:
		Bullet(int x, int y);

		void update(const unsigned char* keys, SDL_Point mousePosition, bool isMouseDown);
		bool shouldDestroy();
		bool processCollisions(vector<GameEntity*> collidingEntities);
		void render(SDL_Renderer* renderer, SDL_Texture* textures[]);
		void setShooter(GameEntity* shooter);
		GameEntity* getShooter();
		vector<GameEntity*> getNewGameEntities();
		void initializeBodyCoordinates();

	private:
		int originalX;
		int originalY;
		GameEntity* shooterEntity;

	};
}
