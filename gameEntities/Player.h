#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include "GameEntity.h"

using namespace std;

namespace GameEntities
{
	class Player : public GameEntity
	{

	private:
		bool isRunning;
		void calculatePosition(const unsigned char* keys);
		void calculateZAngle(SDL_Point mousePosition);
		float getCurrentMovingSpeed();
		void fire(bool isMouseDown);

	public:
		Player(int x, int y);

		void update(const unsigned char* keys, SDL_Point mousePosition, bool isMouseDown);
		bool shouldDestroy();
		void render(SDL_Renderer* renderer, SDL_Texture* textures[]);
		vector<GameEntity*> getNewGameEntities();
	};
}
