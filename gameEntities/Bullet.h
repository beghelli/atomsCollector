#pragma once
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "GameEntity.h"
#include "ScreenWriter.h"

using namespace std;
using namespace Engine;
using namespace Engine::Support;

namespace GameEntities
{
	class Bullet : public GameEntity{

	public:
		Bullet(int x, int y);

		void update(const unsigned char* keys, SDL_Point mousePosition, bool isMouseDown);
		bool shouldDestroy();
		bool isGameOver();
		bool processCollisions(vector<GameEntity*> collidingEntities);
		void render(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter);
		void setShooter(GameEntity* shooter);
		GameEntity* getShooter();
		vector<GameEntity*> getNewGameEntities();

	private:
		int originalX;
		int originalY;
		GameEntity* shooterEntity;

	};
}
